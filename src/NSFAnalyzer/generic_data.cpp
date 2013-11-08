#include "stdafx.h"
#include "search_core.h"

using namespace System::Runtime::InteropServices;
using namespace Windows::Forms;

/*************************************************************************

    FUNCTION:   BuildDbList

    PURPOSE:    Build list of dbs to iterate. Based on the include/exclude options.

    DESCRIPTION: This only fires when no db is selected. (e.g. during a server-wide search).

    INPUTS:     dbStats         - collects stats about the db search list
      pSearchMatch  - information about the note found
      SummaryBuffer - not use

*************************************************************************/
STATUS LNPUBLIC BuildDbList (void *dbStats, 
 						     SEARCH_MATCH far *pSearchMatch,
							 ITEM_TABLE *summary_info)
{
    STATUS        error;
    SEARCH_MATCH SearchMatch;
	char *item_path;

    memcpy( (char*)&SearchMatch, (char*)pSearchMatch, sizeof(SEARCH_MATCH) );
	
	//	Skip this object if it does not really match the search criteria (it 
	//	is now deleted or modified).  This is not necessary for full searches,
	//	but is shown here in case a starting date was used in the search. 

    if (!(SearchMatch.SERetFlags & SE_FMATCH))
        return (NOERROR);

	GCHandle _gcHandle = GCHandle::FromIntPtr(safe_cast<IntPtr>(dbStats));
	NSFScan::ScanIterator^ si = safe_cast<NSFScan::ScanIterator^>(_gcHandle.Target);

	item_path = (char *)malloc(MAXPATH*sizeof(char*));
	*item_path = NULL;

	error = NSFAnalyzerEngine::pNSFGetSummaryValue((ITEM_TABLE *)summary_info, 
						       (char *)("$Path"), 
							   (char *)item_path, 
							   (WORD)MAXPATH);

	if (!error)
	{
		free(item_path);
		return error;
	}

	for (UINT iLen=0; iLen < strlen(item_path); iLen++)
	{
		if (item_path[iLen] == '/') // flip dir slash to win32 format
			item_path[iLen] = '\\';
	}

	String^ currentToken = gcnew String(item_path);
	free(item_path);

	if (si->IsMatch) {
		si->Search_Databases->Add(currentToken);
	} else {	
		String^ searchString = String::Empty;
		for (int i=0; i<si->Search_Tokens->Count; i++) {
			searchString = si->Search_Tokens[i];
			if (si->ExactMatchesOnly) {
				if (currentToken->ToUpper()->StartsWith(searchString->ToUpper())) {
					si->Search_Databases->Add(currentToken);
				}
			} else {
				if (!currentToken->ToUpper()->StartsWith(searchString->ToUpper())) {
					si->Search_Databases->Add(currentToken);
				}
			}
		}
	}	
	return false;
}
/*************************************************************************

    FUNCTION:   ScanNote

    PURPOSE:    Print the contents of one design note -- of any class -- to 
      the dumpfile.

    DESCRIPTION: This is the action routine specified to NSFSearch.

    INPUTS:     Param         - not used
      pSearchMatch  - information about the note found
      SummaryBuffer - not use

*************************************************************************/
STATUS  LNPUBLIC  ScanNote( void far *Param, SEARCH_MATCH far *pSearchMatch, ITEM_TABLE far *SummaryBuffer ) {	
	STATUS					Error;
    SEARCH_MATCH			SearchMatch;    
	char					szFieldName[80] = { 0 };
	NOTEHANDLE				hNote;		

	GCHandle _gcHandle = GCHandle::FromIntPtr(safe_cast<IntPtr>(Param));
	NSFAnalyzerEngine^ scan_engine = safe_cast<NSFAnalyzerEngine^>(_gcHandle.Target);

	bool hasOpenNote = false;

	try {

		if (scan_engine->GetWorkerThread()->CancellationPending) {
			scan_engine->NotifyClient("Operation Canceled!", NSFAnalyzerEngine::PROGRESS_MATCH);
			return THREAD_CANCEL;
		}

		memcpy( (char*)&SearchMatch, (char*)pSearchMatch, sizeof(SEARCH_MATCH) );

		if (!(SearchMatch.SERetFlags & SE_FMATCH)) {			
			return (NOERROR);
		}

		if (Error = scan_engine->pNSFNoteOpen( scan_engine->scanner->hdb, SearchMatch.ID.NoteID, 0, &hNote )) {
			MessageBox::Show("Error: in pNSFNoteOpen. Unable to open Note. id=" + SearchMatch.ID.NoteID + " . Scan aborted", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return Error;
		}
		scan_engine->scanner->CurrentNoteHandle = hNote;
		scan_engine->scanner->ScanCount++; 
		hasOpenNote = true;
		WORD lenFieldName = scan_engine->pNSFItemGetText(hNote, "$TITLE", szFieldName, sizeof(szFieldName)); 		
		scan_engine->scanner->SearchQuery->NoteID = SearchMatch.ID.NoteID;
		scan_engine->scanner->SearchQuery->DesignClass = scan_engine->scanner->GetDesignType((WORD)SearchMatch.NoteClass);
		scan_engine->scanner->SearchQuery->DesignTitle= gcnew String(szFieldName);
	
		scan_engine->NotifyClient("Scanning: " + scan_engine->scanner->SearchQuery->DesignClass + ":" + scan_engine->scanner->SearchQuery->DesignTitle, NSFAnalyzerEngine::PROGRESS_CURRENTACTIVITY);		

		Error = scan_engine->pNSFItemScan(hNote, ScanItem, (void *)Param );
		if (Error != NOERROR) {
			scan_engine->WriteLog("pNSFItemScan failed. Unable to scan the note item: " + scan_engine->scanner->SearchQuery->NoteID);		
		}						

		return NOERROR;

	} catch(Exception^ ex) {
		MessageBox::Show(ex->Message + "\n" + ex->StackTrace, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);		
		return true;

	} finally {
		if (hNote && hasOpenNote) {
			Error = scan_engine->pNSFNoteClose(hNote);
			if (Error != NOERROR) {
				scan_engine->WriteLog("pNSFNoteClose failed. Unable to close note.", true);
				MessageBox::Show("Error: in pNSFNoteOpen. Unable to close the Note. id=" + SearchMatch.ID.NoteID + " . Scan aborted", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				exit(0);
			}
		}
		 
	}
	
}

/************************************************************************

    FUNCTION:   ScanItem

    PURPOSE:    Scan each item.

    ALGORITHM:  This is the action routine specified to NSFItemScan.

*************************************************************************/
STATUS LNPUBLIC ScanItem(WORD Spare, 
						 WORD ItemFlags, 
						 char far *Name, 
						 WORD NameLength, 
						 VOID far *Value, 
						 DWORD ValueLength,
						 void far *Parameter)
{
    char	*pData;
    WORD	length;
    WORD    wDataType;    
    char	TestItemName[80];

	GCHandle _gcHandle = GCHandle::FromIntPtr(safe_cast<IntPtr>(Parameter));
	NSFAnalyzerEngine^ scan_engine = safe_cast<NSFAnalyzerEngine^>(_gcHandle.Target);

	//strncpy(TestItemName, Name, NameLength);
	strncpy_s(TestItemName, Name, NameLength);
    TestItemName[NameLength] = '\0';
	
    pData = (char *) Value;
    length = (WORD) ValueLength; // includes the 2 byte data type
	memcpy((char far *)(&wDataType), pData, sizeof(WORD));
	scan_engine->scanner->SearchQuery->FieldName = gcnew String(TestItemName);


	//scan_engine->WriteLog("Scanning item: " + scan_engine->scanner->SearchQuery->FieldName);
	scan_engine->NotifyClient("Inspecting Item: " +  scan_engine->scanner->SearchQuery->FieldName, NSFAnalyzerEngine::PROGRESS_CURRENTACTIVITY);	
	
    pData += sizeof(WORD);
    length -= sizeof(WORD);

	scan_engine->scanner->SearchQuery->DataType = gcnew String(GetLiteralString(TypeStringTablePtr, wDataType ));
	
	void* ptr = GCHandle::ToIntPtr(GCHandle::Alloc(scan_engine)).ToPointer();
	bool isScanned = false;
	
	switch(wDataType)
	{
	case TYPE_ERROR:
	    break;

	case TYPE_UNAVAILABLE:
	    break;

	case TYPE_TEXT:
		if (length)
			isScanned = true;
			PrintText( pData, (DWORD)length, ptr, "Text");
		break;

	case TYPE_FORMULA:
		isScanned = true;
	    PrintFormula( pData, length, ptr, "Formula");
	    break;

	case TYPE_INVALID_OR_UNKNOWN:
	    break;
   
      case TYPE_COMPOSITE:
		isScanned = true;
        DumpCompoundTextItem( Name, NameLength, pData, length, ptr );
        break;

	case TYPE_COLLATION:
	    break;
 
	case TYPE_NOTEREF_LIST:
	    break;

	case TYPE_VIEW_FORMAT:
	    break;
 
	case TYPE_ICON:
	    break;

	case TYPE_SIGNATURE:
	    break;

	case TYPE_SEAL:
	    break;
     
	case TYPE_SEALDATA:
	    break;

	case TYPE_SEAL_LIST:
	    break;

	case TYPE_HIGHLIGHTS:
	    break;

	case TYPE_WORKSHEET_DATA:
	    break;
		
	case TYPE_LSOBJECT:
		isScanned = true;
		DumpLotusScriptObjectItem ( Name, NameLength, pData, length, ptr, "LotusScript" );
		break;
	
	case TYPE_HTML:
		isScanned = true;
		DumpHTMLItem ( Name, NameLength, pData, length, ptr, "Html");
		break;

	case TYPE_QUERY:
		isScanned = true;
		DumpAgentQueryItem ( Name, NameLength, pData, length, ptr, "Query" );
		break;

	case TYPE_ACTION:
		isScanned = true;
		DumpActionItem ( Name, NameLength, pData, length, ptr, "Action" );
		break;

	case TYPE_ASSISTANT_INFO:
		//DumpAgentInfoItem(Name, NameLength, pData, length);
		break;
	}

	if (length && !isScanned) {
		PrintText( pData, (DWORD)length, ptr);
	}
	
	return 0;
}

bool IsItemName(void far* pScan, String^ itemName) {
	GCHandle _gcHandle = GCHandle::FromIntPtr(safe_cast<IntPtr>(pScan));
	NSFAnalyzerEngine^ scan_engine = safe_cast<NSFAnalyzerEngine^>(_gcHandle.Target);

	for (int i=0; i<scan_engine->scanner->Search_Tokens->Count; i++) {
		if (scan_engine->scanner->SearchQuery->FieldName->ToLower()->Contains(scan_engine->scanner->Search_Tokens[i]->ToLower())) {
			scan_engine->scanner->SearchQuery->MatchToken = scan_engine->scanner->Search_Tokens[i];
			scan_engine->scanner->SearchQuery->MatchType = EXACT_MATCH;
			scan_engine->scanner->SearchQuery->DataType = "Item Name Match";
			scan_engine->WriteLog("Match Found. Token: " + scan_engine->scanner->Search_Tokens[i] + ".\tDesign Class: " + scan_engine->scanner->SearchQuery->DesignClass + ".\tDesign Name: " + scan_engine->scanner->SearchQuery->DesignTitle + ".\tMatch Type: EXACT MATCH.\tField:" + scan_engine->scanner->SearchQuery->FieldName + "\tData Type: " + scan_engine->scanner->SearchQuery->DataType + ".\n\n");
			scan_engine->NotifyClient("Match Found for token: " + scan_engine->scanner->Search_Tokens[i] + " in " + scan_engine->scanner->SearchQuery->DesignClass + ": " + scan_engine->scanner->SearchQuery->DesignTitle + " in database: " + scan_engine->scanner->CurrentDatabase + "  (" + scan_engine->scanner->CurrentDatabaseTitle + ")", NSFAnalyzerEngine::PROGRESS_MATCH);
			return true;
		}
	}
	return false;
}

/*************************************************************************

    FUNCTION:   GetLiteralString

    PURPOSE:    Search the table for a constant that matches the
				dwValue argument, and return the matching string
				pointer.  The last entry in the table must have
				the value LITERAL_TABLE_END.

**************************************************************************/

char * LNPUBLIC GetLiteralString (LITERAL_NAME_ENTRY *pTable, DWORD dwValue) 
{
		/* Scan the table for a match or the end marker */
	while ((LITERAL_TABLE_END != pTable->dwValue) && (dwValue != pTable->dwValue))
		pTable++;

		/* Return the pointer to the string */
	return (pTable->pName);
}

/************************************************************************

    FUNCTION:   searchBuffer

    PURPOSE:    Search a (formula) buffer for a keyword match

    INPUTS:
				char   *scanBuf - pointer to start of data to search

*************************************************************************/
void searchBuffer(char *scanBuf, void * pScanEngine) {	
	searchBuffer(scanBuf, pScanEngine, String::Empty);
}	

void searchBuffer(char *scanBuf, void * pScanEngine, String^ details) {	
	String^ scanBuffer = gcnew String(scanBuf);
	NSFScan::ScanResult^ result;

	GCHandle _gcHandle = GCHandle::FromIntPtr(safe_cast<IntPtr>(pScanEngine));
	NSFAnalyzerEngine^ scan_engine = safe_cast<NSFAnalyzerEngine^>(_gcHandle.Target);
	
	if (scan_engine->scanner->SearchQuery->MatchType != NO_MATCH) {
		return; // previous item had a match, we can stop scanning the other items on this note.
	}
	//scan_engine->WriteLog(scan_engine->scanner->SearchQuery->DesignClass + "; " + scan_engine->scanner->SearchQuery->DesignTitle + "; " + scan_engine->scanner->SearchQuery->FieldName->ToLower());

	for (int i=0; i<scan_engine->scanner->Search_Tokens->Count; i++) {
		if (scanBuffer->ToLower()->Contains(scan_engine->scanner->Search_Tokens[i]->ToLower())) {
			scan_engine->scanner->SearchQuery->MatchToken = scan_engine->scanner->Search_Tokens[i];
			scan_engine->scanner->SearchQuery->MatchType = EXACT_MATCH;
			scan_engine->WriteLog("Match Found. Token: " + scan_engine->scanner->Search_Tokens[i] + ".\tDesign Class: " + scan_engine->scanner->SearchQuery->DesignClass + ".\tDesign Name: " + scan_engine->scanner->SearchQuery->DesignTitle + ".\tMatch Type: EXACT MATCH.\tField:" + scan_engine->scanner->SearchQuery->FieldName + "\tData Type: " + scan_engine->scanner->SearchQuery->DataType + ".\n\n");
			scan_engine->NotifyClient("Match Found for token: " + scan_engine->scanner->Search_Tokens[i] + " in " + scan_engine->scanner->SearchQuery->DesignClass + ": " + scan_engine->scanner->SearchQuery->DesignTitle + " in database: " + scan_engine->scanner->CurrentDatabase + "  (" + scan_engine->scanner->CurrentDatabaseTitle + ")", NSFAnalyzerEngine::PROGRESS_MATCH);

			scan_engine->scanner->IsMatch = true;	// signal that at least one entry had a match			
			scan_engine->scanner->MatchCount++;
			result = gcnew NSFScan::ScanResult();
			result->DatabaseFile = scan_engine->scanner->SearchQuery->DatabaseFile;
			result->DataType = scan_engine->scanner->SearchQuery->DataType;
			result->DesignClass = scan_engine->scanner->SearchQuery->DesignClass;
			result->DesignTitle = scan_engine->scanner->SearchQuery->DesignTitle;			
			result->FieldName = scan_engine->scanner->SearchQuery->FieldName;
			result->Details = details;			
			result->MatchToken = scan_engine->scanner->SearchQuery->MatchToken;
			result->MatchType = scan_engine->scanner->SearchQuery->MatchType;
			result->NoteID = scan_engine->scanner->SearchQuery->NoteID;
			scan_engine->scanner->AddSearchResult(result);
			scan_engine->scanner->SearchQuery->MatchType = NO_MATCH; // reset query;								
			
		}
	}
	
	// no match found yet
	if (false == scan_engine->scanner->ExactMatchesOnly) {
		// we have been asked to look for possible match
		if (scanBuffer->ToLower()->Contains("%include")) {
			scan_engine->scanner->SearchQuery->MatchType = POSSIBLE_MATCH;
			scan_engine->scanner->SearchQuery->MatchToken = "%INCLUDE";
			scan_engine->WriteLog("Match Found. Token: %\'Include\'.\tDesign Class: " + scan_engine->scanner->SearchQuery->DesignClass + ".\tDesign Name: " + scan_engine->scanner->SearchQuery->DesignTitle + ".\tMatch Type: EXACT MATCH.\tField:" + scan_engine->scanner->SearchQuery->FieldName + "\tData Type: " + scan_engine->scanner->SearchQuery->DataType + ".\n\n");	
			scan_engine->NotifyClient("Ambigious/Possible Match Found - %INCLUDE statement found in " + scan_engine->scanner->SearchQuery->DesignClass + ": " + scan_engine->scanner->SearchQuery->DesignTitle , NSFAnalyzerEngine::PROGRESS_MATCH);

			scan_engine->scanner->IsMatch = true;	// signal that at least one entry had a match			
			scan_engine->scanner->MatchCount++;
			result = gcnew NSFScan::ScanResult();
			result->DatabaseFile = scan_engine->scanner->SearchQuery->DatabaseFile;
			result->DataType = scan_engine->scanner->SearchQuery->DataType;
			result->DesignClass = scan_engine->scanner->SearchQuery->DesignClass;
			result->DesignTitle = scan_engine->scanner->SearchQuery->DesignTitle;			
			result->FieldName = scan_engine->scanner->SearchQuery->FieldName;
			result->Details = details;
			result->MatchToken = scan_engine->scanner->SearchQuery->MatchToken;
			result->MatchType = scan_engine->scanner->SearchQuery->MatchType;
			result->NoteID = scan_engine->scanner->SearchQuery->NoteID;
			scan_engine->scanner->AddSearchResult(result);
			scan_engine->scanner->SearchQuery->MatchType = NO_MATCH; // reset query;		

		}
	}	

}
/************************************************************************

    FUNCTION:   PrintText

    PURPOSE:    Print a block of ascii text

    INPUTS:
   char   *pPtr;                   pointer to start of data
   DWORD   dwCharacters;           number of characters to print

*************************************************************************/

void PrintText(char far *pPtr, DWORD dwCharacters, void *pScan) {
	searchBuffer(pPtr, pScan);	
}

void PrintText(char far *pPtr, DWORD dwCharacters, void *pScan, String^ details) {
	searchBuffer(pPtr, pScan, details);	
}
/*************************************************************************

    FUNCTION:   PrintFormula

    PURPOSE:    Decompile the formula and write to output file.

**************************************************************************/
void PrintFormula (char far *pFormula, WORD formulaLen, void * pScan) {
	PrintFormula(pFormula, formulaLen, pScan, String::Empty);
}

void PrintFormula (char far *pFormula, WORD formulaLen, void * pScan, String^ details) {
	STATUS          error;
	HANDLE          hFormulaText;
	WORD            wFormulaTextLength;
	char far *      pFormulaText;

	if( formulaLen == 0 )
	{
		// empty formula is ok, skip
	} else if (error = NSFAnalyzerEngine::pNSFFormulaDecompile (pFormula, 
										  FALSE, 
										  &hFormulaText, 
										  &wFormulaTextLength )) 
	{
		char errBuffer[256];
		NSFAnalyzerEngine::pOSLoadString(NULLHANDLE, error, errBuffer, 256);
		GCHandle _gcHandle = GCHandle::FromIntPtr(safe_cast<IntPtr>(pScan));
		NSFAnalyzerEngine^ scan_engine = safe_cast<NSFAnalyzerEngine^>(_gcHandle.Target);
		scan_engine->WriteLog(gcnew String(errBuffer), true);
    } else
    {
		pFormulaText = (char*) NSFAnalyzerEngine::pOSLockObject( hFormulaText );		
		PrintText( pFormulaText, wFormulaTextLength, pScan, details);
		NSFAnalyzerEngine::pOSUnlockObject( hFormulaText );
		NSFAnalyzerEngine::pOSMemFree( hFormulaText );
    }
}


/************************************************************************

    FUNCTION:   DumpLotusScriptObjectItem

************************************************************************/
void DumpLotusScriptObjectItem (char *Name, WORD NameLength, char *pData, WORD length, void *pScan) {	
	DumpLotusScriptObjectItem(Name, NameLength, pData, length, pScan, String::Empty);

	return;
}

void DumpLotusScriptObjectItem (char *Name, WORD NameLength, char *pData, WORD length, void *pScan, String^ details) {
	PrintFormula(pData, length, pScan, details + " (LS Object length: " + length + ")");
	return;
}


/************************************************************************

    FUNCTION:   DumpHTMLItem

************************************************************************/
void DumpHTMLItem(char *Name, WORD NameLength, char *pData, WORD length, void *pScan) {	
	DumpHTMLItem(Name, NameLength, pData, length, pScan, String::Empty);
	return;
}
void DumpHTMLItem(char *Name, WORD NameLength, char *pData, WORD length, void *pScan, String^ d) {	
	PrintText (pData, length, pScan, d );	
	return;
}

/*************************************************************************

    FUNCTION:   PrintScriptSource

    PURPOSE:    Write text form of script to output file.

**************************************************************************/
void PrintScriptSource (char far *pScript, DWORD scriptLen, void *pScan) {
	PrintText (pScript, (WORD) scriptLen, pScan, String::Empty);
}

void PrintScriptSource (char far *pScript, DWORD scriptLen, void *pScan, String^ details) {
	PrintText (pScript, (WORD) scriptLen, pScan, details);
}

/*************************************************************************

    FUNCTION:   PrintCompositeBuffer

    PURPOSE:    For each CD record in the buffer, call the action routine.
				This function is similar to EnumCompositeBuffer(), but is
				not limited to items of TYPE_TEXT or TYPE_COMPOSITE.  This
				routine also takes a pointer as an argument, rather than
				a BLOCKID.  Just like EnumCompositeBuffer(), this routine
				will quit if a non-zero status code is returned from the
				callback.  If the status code ERR_ODS_ENUM_COMPLETE is
				returned, this routine will return NOERROR to the caller.

**************************************************************************/
STATUS LNPUBLIC PrintCompositeBuffer (char FAR *pBuffer, DWORD ItemValueLength, ActionRoutinePtr ActionRoutine, void *pScan) {
	STATUS error = NOERROR;
	char FAR *Endptr;

	GCHandle _gcHandle = GCHandle::FromIntPtr(safe_cast<IntPtr>(pScan));
	NSFAnalyzerEngine^ scan_engine = safe_cast<NSFAnalyzerEngine^>(_gcHandle.Target);

	/* Loop through the composite buffer. */
	Endptr = pBuffer + ItemValueLength;

	while (pBuffer < Endptr)
	{
		char    *RecordStart = pBuffer;
		WORD    RecordType, Length,FixedSize;
		DWORD   RecordLength;

		/*      Get the signature of the record.  The first byte is the SIG_xxx
			value, and the second byte is a code which indicates the number
			of bits necessary to hold the record's length. */
		NSFAnalyzerEngine::pODSReadMemory(&pBuffer, _WORD, &RecordType, 1);
		switch (RecordType & 0xFF00)
		{
			case LONGRECORDLENGTH:
				NSFAnalyzerEngine::pODSReadMemory(&pBuffer, _DWORD, &RecordLength, 1);
				FixedSize = sizeof(LSIG);
				break;

			case WORDRECORDLENGTH:
				NSFAnalyzerEngine::pODSReadMemory(&pBuffer, _WORD, &Length, 1);
				RecordLength = (DWORD) Length;
				FixedSize = sizeof(WSIG);
				break;

			default:
				RecordLength = (DWORD) ((RecordType >> 8) & 0x00FF);
				RecordType &= 0x00FF; /* Length not part of signature */
				FixedSize = sizeof(BSIG);
				break;
		}
		
		// Call the action routine with the pointer to the record, the	type, length, and any context.

		if (error = (*ActionRoutine)(RecordStart, RecordType, RecordLength, pScan))
			break;

		//      Advance to the next record.

		if (RecordLength)
			 pBuffer = RecordStart + RecordLength;
		else
			 pBuffer = RecordStart + FixedSize;

		if (1 & ((WORD)pBuffer))      //pad record length if odd
			pBuffer++;                //(all records are word aligned)

	} // end while

	if (ERR_ODS_ENUM_COMPLETE == error)
		error = NOERROR;

	return(error);	
}

/************************************************************************

   FUNCTION:   GetTDString

*************************************************************************/
void LNPUBLIC GetTDString(TIMEDATE * ptdModified, char * szTimedate) {
    WORD            wLen;

	NSFAnalyzerEngine::pConvertTIMEDATEToText( NULL, NULL, 
			    ptdModified, 
			    szTimedate, 
			    MAXALPHATIMEDATE,
			    &wLen );
    szTimedate[wLen] = '\0';
    return;
}

/*************************************************************************

    FUNCTION:   PrintCanonicalValue

    PURPOSE:    Print an arbitrary Notes computable data type, given
				a pointer to the data, the type, and the length.

**************************************************************************/
void PrintCanonicalValue (char *pValue, WORD wType, WORD wValueLen, void *pScan){
	PrintCanonicalValue(pValue, wType, wValueLen, pScan, String::Empty);
}

void PrintCanonicalValue (char *pValue, WORD wType, WORD wValueLen, void *pScan, String^ d){
	switch (wType){
		case TYPE_TEXT:
			PrintText (pValue, wValueLen, pScan, d);
			break;

		case TYPE_TEXT_LIST:
			DumpTextlistItem (pValue, wValueLen, pScan);
			break;

		case TYPE_NUMBER:
			 DumpNumberItem (pValue, wValueLen);
			 break;

		case TYPE_NUMBER_RANGE:
			DumpNumberRangeItem (pValue, wValueLen);
			break;

		case TYPE_TIME:
			DumpTimeItem (pValue, wValueLen);
			break;

		case TYPE_TIME_RANGE:
			DumpTimeRangeItem (pValue, wValueLen);
			break;
			
			default:
				//Not a computable data type
				break;
	}

	return;
}

/************************************************************************

    FUNCTION:   DumpOneActionRecord

    PURPOSE:    Dump one Action Record

    ALGORITHM:  This is the action routine for EnumCompositeBuffer
                specified in DumpActionItem().

    INPUTS:      
         char      *RecordPtr       -   pointer to start of CD record data
                                        This data is in Canonical format.
         WORD       RecordType      -   CD record type (SIG_ACTION_*)
         DWORD      RecordLength    -   length of CD record
         void far * Unused

*************************************************************************/
STATUS LNPUBLIC DumpOneActionRecord(char *RecordPtr, WORD RecordType, DWORD RecordLength, void *pScan ) {
    switch (RecordType) 
    {
			/* Agent CD records - added in Releae 4.0 */
		case SIG_ACTION_HEADER:
			DumpActionHeader( RecordPtr, RecordLength );
			break;

		case SIG_ACTION_MODIFYFIELD:
			DumpActionModifyfield( RecordPtr, RecordLength, pScan);
			break;

		case SIG_ACTION_REPLY:
			DumpActionReply( RecordPtr, RecordLength, pScan );
			break;

		case SIG_ACTION_FORMULA:

		case SIG_ACTION_FORMULAONLY:
			DumpActionFormula( RecordPtr, RecordLength, RecordType, pScan );
			break;

		case SIG_ACTION_LOTUSSCRIPT:
			DumpActionLotusscript( RecordPtr, RecordLength, pScan );
			break;

		case SIG_ACTION_SENDMAIL:
			DumpActionSendmail( RecordPtr, RecordLength, pScan );
			break;

		case SIG_ACTION_DBCOPY:
			DumpActionDbcopy( RecordPtr, RecordLength, pScan );
			break;

		case SIG_ACTION_DELETE:
			//DumpActionDelete( RecordPtr, RecordLength );
			break;

		case SIG_ACTION_BYFORM:
			DumpActionByform( RecordPtr, RecordLength, pScan );
			break;

		case SIG_ACTION_MARKREAD:
		case SIG_ACTION_MARKUNREAD:
			//DumpActionReadMarks(RecordPtr, RecordLength, RecordType);
			break;

		case SIG_ACTION_MOVETOFOLDER:
		case SIG_ACTION_COPYTOFOLDER:
		case SIG_ACTION_REMOVEFROMFOLDER:
			DumpActionFolder( RecordPtr, RecordLength, RecordType, pScan );
			break;

		case SIG_ACTION_NEWSLETTER:
			DumpActionNewsletter( RecordPtr, RecordLength, pScan );
			break;

		case SIG_ACTION_RUNAGENT:
			DumpActionRunagent( RecordPtr, RecordLength, pScan );
			break;

		case SIG_ACTION_SENDDOCUMENT:
			//DumpActionSenddocument( RecordPtr, RecordLength );
			break;

			/* New in Release 4.6 */
		case SIG_ACTION_JAVAAGENT:
			DumpActionJavaAgent( RecordPtr, RecordLength, pScan );
			break;

        default:
			NSFDDUMPDumpMemory( RecordPtr, (WORD) RecordLength, pScan );
            break;
	}
   return NOERROR;
}

/************************************************************************

    FUNCTION:   DumpOneAgentQueryRecord

    PURPOSE:    Dump one Agent Query Record

    ALGORITHM:  This is the action routine for EnumCompositeBuffer
                specified in DumpAgentQueryItem().

    INPUTS:      
         char      *RecordPtr       -   pointer to start of CD record data
                                        This data is in Canonical format.
         WORD       RecordType      -   CD record type (SIG_QUERY_*)
         DWORD      RecordLength    -   length of CD record
         void far * Unused

*************************************************************************/
STATUS LNPUBLIC DumpOneAgentQueryRecord(char *RecordPtr, WORD RecordType, DWORD RecordLength, void *pScan ) {
	String^ d = "Agent. Bytes: " + RecordLength + ", Record Type: ";

    switch (RecordType) 
    {
			/* Agent CD records - added in Releae 4.0 */
		
		case SIG_QUERY_HEADER:
			d += "Query Header.";
			DumpQueryHeader( RecordPtr, RecordLength, pScan, d );
			break;

		case SIG_QUERY_TEXTTERM:
			d += "Query Text Term.";
			DumpQueryTextterm( RecordPtr, RecordLength, pScan, d );
			break;

		case SIG_QUERY_BYFIELD:
			d += "Query By Field.";
			DumpQueryByfield(RecordPtr, RecordLength, RecordType, pScan, d );
			break;

		case SIG_QUERY_BYDATE:
			d += "Query By Date.";
			DumpQueryByfield(RecordPtr, RecordLength, RecordType, pScan, d );
			break;

		case SIG_QUERY_BYAUTHOR:
			d += "Query By Author.";
			DumpQueryByfield(RecordPtr, RecordLength, RecordType, pScan, d );
			break;

		case SIG_QUERY_FORMULA:
			d += "Query By Formula.";
			DumpQueryFormula( RecordPtr, RecordLength, pScan, d);
			break;

		case SIG_QUERY_BYFORM:
			d += "Query By Form.";
			DumpQueryByform( RecordPtr, RecordLength, pScan, d );
			break;

		case SIG_QUERY_BYFOLDER:
			d += "Query By Folder.";
			DumpQueryByfolder( RecordPtr, RecordLength, pScan, d );
			break;

		case SIG_QUERY_USESFORM:
			d += "Query uses form.";
			DumpQueryUsesform(RecordPtr, RecordLength, pScan, d );
			break;

		case SIG_QUERY_TOPIC:
			//DumpQueryTopic( RecordPtr, RecordLength );
			break;
	
        default:
			d += "Agent Query";
            NSFDDUMPDumpMemory( RecordPtr, (WORD) RecordLength, pScan, d );
            break;
   }
   return NOERROR;
}

/************************************************************************

    FUNCTION:   PickApartTime

	PURPOSE:	Divide a time value into hours, minutes, seconds, and
				milliseconds (NOT ticks!!)

************************************************************************/
void PickApartTime (DWORD time, WORD *pHours, WORD *pMinutes, WORD *pSeconds, WORD *pMillies) {
	*pHours = (WORD) (time / TICKS_IN_HOUR);
	time %= TICKS_IN_HOUR;
	*pMinutes = (WORD) (time / TICKS_IN_MINUTE);
	time %= TICKS_IN_MINUTE;
	*pSeconds = (WORD) (time / TICKS_IN_SECOND);
	time %= TICKS_IN_SECOND;
	*pMillies = (WORD) (10 * time);
}


/************************************************************************

    FUNCTION:   DumpODSAssistFieldStruct

	PURPOSE:	Dump the contents of the individual field sub-records.

	ARGUMENTS:
		ppData		Address of pointer variable;  this pointer is moved
					to the first byte following the field structure
					on return.
		pIndent		Prefix string so printing is pretty.

*************************************************************************/
void LNPUBLIC DumpODSAssistFieldStruct (char **ppData, char *pIndent, LITERAL_NAME_ENTRY *pTable, void *pScan) {
	char *					p = *ppData;
	ODS_ASSISTFIELDSTRUCT	FieldStruct;
	char *					pName;		/* Name for constant value */

	NSFAnalyzerEngine::pODSReadMemory (&p, _ODS_ASSISTFIELDSTRUCT, &FieldStruct, 1);

	pName = GetLiteralString (pTable, FieldStruct.wOperator);
	pName = GetLiteralString (TypeStringTablePtr, FieldStruct.wValueDataType);
	if (FieldStruct.wFieldNameLen)
	{
		PrintText (p, FieldStruct.wFieldNameLen, pScan);
		p += FieldStruct.wFieldNameLen;
	}

	PrintCanonicalValue (p, FieldStruct.wValueDataType, FieldStruct.wValueLen, pScan, "ODS Assist Field Structure");

	*ppData += FieldStruct.wTotalLen;
	return;
}


/************************************************************************

    FUNCTION:   NSFDDUMPDumpMemory

    PURPOSE:    Print memory in HEX side-by-side with ASCII representation

    INPUTS:     char *   pData           pointer to start of memory to dump
				WORD     wSize           size in bytes of memory to dump

*************************************************************************/
void NSFDDUMPDumpMemory(char * pData, WORD wSize, void *pScanEngine ) {   
	NSFDDUMPDumpMemory(pData, wSize, pScanEngine, String::Empty);
}

void NSFDDUMPDumpMemory(char * pData, WORD wSize, void *pScanEngine, String^ details ) {                   
    WORD    wCount;             /* How many bytes have been printed */
    WORD    wDumped;            /* Where we are on this line */
    WORD    wOffset;            /* Offset to first byte */
    char    chASCII[17] = "";           
    char    *pLocal;

	GCHandle _gcHandle = GCHandle::FromIntPtr(safe_cast<IntPtr>(pScanEngine));
	NSFAnalyzerEngine^ scan_engine = safe_cast<NSFAnalyzerEngine^>(_gcHandle.Target);

    pLocal = pData;
    wCount = wDumped = wOffset = 0;
    if (wSize < 1) {   
		scan_engine->WriteLog("Error: NSFDDUMPDumpMemory: Size less than one (1)", true);
		return;                                      
    }               

    while (wCount < wSize) {    
		wOffset = LOWORD((WORD)pLocal) & 0x000F;
		wDumped = 0;

		/* Fill in any leading blanks */
		for ( ; wDumped < wOffset; wDumped++){ /* Start with current value of wDumped */
			chASCII[wDumped] = ' ';
		}

	    /* Print any data on this line */
		for ( ; (wDumped < 16) && (wCount < wSize); wDumped++){
			/* Start with current value of wDumped */
	    
			/* exclude non-printing ASCII */
		    chASCII[wDumped] = (char) ((*pLocal < 0x20 || *pLocal > 0x7E) ? 0x2E : *pLocal);
	
		    pLocal++;
			wCount++;
		}

		/* Fill in any trailing blanks */
		for ( ; wDumped < 16; wDumped++) {
			//fprintf (activitylog, "   ");
			chASCII[wDumped] = ' ';
		}

		chASCII[wDumped] = '\0';
	
    }
	
	PrintText(chASCII, wDumped, pScanEngine, details);

	scan_engine->WriteLog("Unknown memory dump: " + gcnew String(chASCII));
    return;
}

/************************************************************************

    FUNCTION:   DumpTextlistItem

*************************************************************************/
void LNPUBLIC DumpTextlistItem(char * pData, WORD length, void *pScan ) {
    LIST   *pList;
    WORD    wEntry;
    char   *pText;
    WORD    wTextSize;

    pList = (LIST*) pData;

    for (wEntry = 0; wEntry  < pList->ListEntries; wEntry++) {		
		NSFAnalyzerEngine::pListGetText( pList, FALSE, wEntry, &pText, &wTextSize );

		if (0 != wTextSize) {
			PrintText(pText, wTextSize, pScan, "Text List Item");
		}
    }
    return;
}


/************************************************************************

    FUNCTION:   DumpNumberItem

    PURPOSE:    print the value of an item of TYPE_NUMBER

    DESCRIPTION:
	First use memcpy to copy the NUMBER pointed to by pData into 
	a local variable. Then print the floating point double value 
	using fprintf.

*************************************************************************/
void LNPUBLIC DumpNumberItem(char *pData, WORD wLength ){
    double    num;
    
    memcpy( (char*)&num, pData, sizeof(NUMBER) );
}


/************************************************************************

    FUNCTION:   DumpNumberRangeItem

*************************************************************************/
void LNPUBLIC DumpNumberRangeItem(char * pData, WORD wLength) {
    RANGE    Range;
    WORD     wEntry;
    double   Number;

    /*   Get the RANGE structure from the location pointed to by pData */
    memcpy( (char*)&Range, pData, sizeof(RANGE) );

    /*   the first Number starts right after the RANGE structure */
    pData += sizeof(RANGE);

    /* For each item, get the number and use fprintf to display it. */
    for (wEntry = 0; wEntry < Range.ListEntries; wEntry++) {
		memcpy( (char*)&Number, pData, sizeof(double) );
		pData += sizeof(double);
    }
}

/************************************************************************

    FUNCTION:   DumpTimeItem

*************************************************************************/
void LNPUBLIC DumpTimeItem(char * pData, WORD wLength) {
    char szTimedate[MAXALPHATIMEDATE+1];

    GetTDString( (TIMEDATE*)pData, szTimedate );
}


/************************************************************************

    FUNCTION:   DumpTimeRangeItem

*************************************************************************/
void    LNPUBLIC  DumpTimeRangeItem(char * pData, WORD wLength) {
    RANGE       Range;
    TIMEDATE    TimeDate;
    TIMEDATE_PAIR TimeDatePair;
    USHORT      usListEntry;
    USHORT      usRangeEntry; 
    char        szTimedate[MAXALPHATIMEDATE+1];
    char        szUpperTD[MAXALPHATIMEDATE+1];

    /* Get the RANGE from the location specified by pData */
    memcpy( (char*)&Range, pData, sizeof(RANGE) ); 

    /* Advance pData to point to the first TIMEDATE in the array */
    pData += sizeof(RANGE);

    /* First print the list entries, then the range entries.*/

    for (usListEntry = 0; usListEntry < Range.ListEntries; usListEntry++) 
    {
		memcpy( (char*)&TimeDate, pData, sizeof(TIMEDATE) );
		pData += sizeof(TIMEDATE);
		GetTDString( &TimeDate, szTimedate );
    }

    for (usRangeEntry = 0; usRangeEntry < Range.RangeEntries; usRangeEntry++)
    {
		memcpy( (char*)&TimeDatePair, pData, sizeof(TIMEDATE_PAIR) );
		pData += sizeof(TIMEDATE_PAIR);
		GetTDString( &TimeDatePair.Lower, szTimedate );
		GetTDString( &TimeDatePair.Upper, szUpperTD );
    }
}

/*************************************************************************

    FUNCTION:   PrintUNID

    PURPOSE:    Write the UNID to the output file.

**************************************************************************/
void LNPUBLIC PrintUNID (UNID *pUnid, void *ptr) {
    char szTimedate[MAXALPHATIMEDATE+1];

	GCHandle _gcHandle = GCHandle::FromIntPtr(safe_cast<IntPtr>(ptr));
	NSFAnalyzerEngine^ scan_engine = safe_cast<NSFAnalyzerEngine^>(_gcHandle.Target);

	scan_engine->WriteLog("\tUNID.File = " + String::Format("{0,10:X}", pUnid->File.Innards[1]) + " - " + String::Format("{0,10:X}", pUnid->File.Innards[0]));

    GetTDString( &(pUnid->Note), szTimedate );
}

/*************************************************************************

    FUNCTION:   PrintNOTELINK

    PURPOSE:    Write the NOTELINK components to the output file.

**************************************************************************/
void LNPUBLIC PrintNOTELINK(NOTELINK *pLink, void *ptr) {
	GCHandle _gcHandle = GCHandle::FromIntPtr(safe_cast<IntPtr>(ptr));
	NSFAnalyzerEngine^ scan_engine = safe_cast<NSFAnalyzerEngine^>(_gcHandle.Target);

	scan_engine->WriteLog("\tLink Replica ID = " + String::Format("{0,10:X}", pLink->File.Innards[1]) + " - " + String::Format("{0,10:X}", pLink->File.Innards[0]));

    PrintUNID( &(pLink->View), ptr);
	scan_engine->WriteLog("\tLink:");
    PrintUNID( &(pLink->Note), ptr);
}

/************************************************************************

    FUNCTION:   DumpHSOleRichText

*************************************************************************/
void LNPUBLIC DumpHSOleRichText(char *RecordPtr, DWORD RecordLength, void *ptr) {
    char far *                  p = RecordPtr;
    HSOLERICHTEXT               hsOleRichText;

	NSFAnalyzerEngine::pODSReadMemory (&p, _HSOLERICHTEXT, &hsOleRichText, 1);

	PrintText (p, hsOleRichText.cFileObjName, ptr, "HS Ole Rich Text");
	p += hsOleRichText.cFileObjName;

    return;
}

/*************************************************************************

    FUNCTION:   DumpActiveObject

    PURPOSE:    Print the Domino and Notes active object records in the
	            specified buffer.

**************************************************************************/
void LNPUBLIC DumpActiveObject (char *RecordPtr, DWORD RecordLength, void *ptr) {
    char far *      p = RecordPtr;
	ACTIVEOBJECT    activeObject;

    NSFAnalyzerEngine::pODSReadMemory (&p, _ACTIVEOBJECT, &activeObject, 1);

	/* Check record version number */
	if (ACTIVEOBJECT_VERSION1 != activeObject.Version) 	
		return;
	
	
	if (0 != activeObject.DocURLNameLength) {
		PrintText (p, activeObject.DocURLNameLength, ptr, "Active Object::URL Name");
		p += activeObject.DocURLNameLength;
	}

	/* Print the codebase string */	
	if (0 != activeObject.CodebaseLength) {
		PrintText (p, activeObject.CodebaseLength, ptr, "Active Object::Code Base");
		p += activeObject.CodebaseLength;
	}

	/* Print the code string */	
	if (0 != activeObject.CodeLength) {
		PrintText (p, activeObject.CodeLength, ptr, "Active Object::Code Length");
		p += activeObject.CodeLength;
	}

		/* Print the object name string */
	if (0 != activeObject.ObjectNameLength) {
		PrintText (p, activeObject.ObjectNameLength, ptr, "Active Object::Object Name");
		p += activeObject.ObjectNameLength;
	}

		/* Print the parameter records */
	for (int index = 0; index < activeObject.ParamCount; index++) {
		DumpActiveObjectParameter (index, &p, ptr);
	}

		/* Print the storage link records */
	for (int index = 0; index < activeObject.StorageLinkCount; index++)	{
		DumpActiveObjectLink (index, &p, ptr);
	}

	return;
}

/*************************************************************************

    FUNCTION:   DumpActiveObjectParameter

    PURPOSE:    Print the Domino and Notes active object parameter record.

**************************************************************************/
void LNPUBLIC DumpActiveObjectParameter (int index,	char **ppRecord, void *ptr) {
    char far *          p = *ppRecord;
	ACTIVEOBJECTPARAM       objectParam;

    NSFAnalyzerEngine::pODSReadMemory (&p, _ACTIVEOBJECTPARAM, &objectParam, 1);

	PrintText (p, objectParam.Length, ptr);
	p += objectParam.Length;

		/* Print the formula, if any */
	if (0 != objectParam.FormulaLength) {
		PrintFormula (p, objectParam.FormulaLength, ptr, "Active Object Parameter");
		p += objectParam.FormulaLength;
	}

	/* Update caller's pointer to start of next record */
	*ppRecord = p;

	return;
}

/*************************************************************************

    FUNCTION:   DumpActiveObjectLink

    PURPOSE:    Print the Domino and Notes active object link record.

**************************************************************************/
void LNPUBLIC DumpActiveObjectLink (int index, char **ppRecord, void *ptr) {
    char far *          p = *ppRecord;
	ACTIVEOBJECTSTORAGELINK objectLink;

	NSFAnalyzerEngine::pODSReadMemory (&p, _ACTIVEOBJECTSTORAGELINK, &objectLink, 1);

	/* Print the link data */
    PrintText (p, objectLink.Length, ptr, "Active Object Link");
	p += objectLink.Length;

	/* Update caller's pointer to start of next record */
	*ppRecord = p;

	return;
}