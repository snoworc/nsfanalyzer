#include "stdafx.h"
#include "search_core.h"

using namespace System::Runtime::InteropServices;
using namespace ICSharpCode::SharpZipLib;
using namespace ICSharpCode::SharpZipLib::Zip;
/************************************************************************

    FUNCTION:   DumpActionHeader

*************************************************************************/
void LNPUBLIC DumpActionHeader(char *RecordPtr, DWORD RecordLength) {
    return;
}

/************************************************************************

    FUNCTION:   DumpActionModifyfield

*************************************************************************/
void LNPUBLIC DumpActionModifyfield (char *RecordPtr, DWORD RecordLength, void *pScan) {
    char far *p = RecordPtr;
    CDACTIONMODIFYFIELD	ActModFieldRec;

	NSFAnalyzerEngine::pODSReadMemory(&p, _CDACTIONMODIFYFIELD, &ActModFieldRec, 1);

	if (ActModFieldRec.wFieldNameLen) {
		PrintText (p, ActModFieldRec.wFieldNameLen, pScan, "Action Modify::Field Name");
		p += ActModFieldRec.wFieldNameLen;
	}
	
	if (ActModFieldRec.wValueLen) {
		PrintText (p, ActModFieldRec.wValueLen, pScan, "Action Modify::Value");
		p += ActModFieldRec.wValueLen;
	}
	
    return;
}

/************************************************************************

    FUNCTION:   DumpActionReply

*************************************************************************/
void LNPUBLIC DumpActionReply(char *RecordPtr, DWORD RecordLength, void *pScan) {
    char far *		p = RecordPtr;
    CDACTIONREPLY	ActReplyRec;

	NSFAnalyzerEngine::pODSReadMemory (&p, _CDACTIONREPLY, &ActReplyRec, 1);

	if (ActReplyRec.wBodyLen)
		PrintText (p, ActReplyRec.wBodyLen, pScan, "Action Reply");

	return;
}

/************************************************************************

    FUNCTION:   DumpActionFormula
	
	PURPOSE:	Dump the contents of a CDACTIONFORMULA record - used for
				SIG_ACTION_FORMULA and SIG_ACTION_FORMULAONLY.

*************************************************************************/
void LNPUBLIC DumpActionFormula(char *RecordPtr, DWORD RecordLength, WORD RecordType, void *pScan) {
    char far *		p = RecordPtr;
    CDACTIONFORMULA	ActFormulaRec;
	
    NSFAnalyzerEngine::pODSReadMemory (&p, _CDACTIONFORMULA, &ActFormulaRec, 1);
	PrintFormula (p, ActFormulaRec.wFormulaLen, pScan, "Action Formula");

    return;
}

/************************************************************************

    FUNCTION:   DumpActionLotusscript

*************************************************************************/
void LNPUBLIC DumpActionLotusscript(char *RecordPtr, DWORD RecordLength, void *pScan) {
    char far *		p = RecordPtr;
    CDACTIONLOTUSSCRIPT	ActScriptRec;

    NSFAnalyzerEngine::pODSReadMemory (&p, _CDACTIONLOTUSSCRIPT, &ActScriptRec, 1);

	PrintScriptSource(p, ActScriptRec.dwScriptLen, pScan, "Action::LotusScript");

    return;
}

/************************************************************************

    FUNCTION:   DumpActionSendmail

*************************************************************************/
void LNPUBLIC DumpActionSendmail(char *	RecordPtr, DWORD RecordLength, void *pScan) {
    char far *p	= RecordPtr;
    CDACTIONSENDMAIL	ActSendMailRec;

    NSFAnalyzerEngine::pODSReadMemory (&p, _CDACTIONSENDMAIL, &ActSendMailRec, 1);

	if (ActSendMailRec.wFieldLen[ACTIONSENDMAIL_TOFIELD]) {
		if (ACTIONSENDMAIL_FLAG_TOFORMULA & ActSendMailRec.dwFlags)
			PrintFormula (p, ActSendMailRec.wFieldLen[ACTIONSENDMAIL_TOFIELD], pScan, "Action Formula::Send Mail::Send To");
		else
			PrintText (p, ActSendMailRec.wFieldLen[ACTIONSENDMAIL_TOFIELD], pScan, "Action Text::Send Mail::Send To");
		p += ActSendMailRec.wFieldLen[ACTIONSENDMAIL_TOFIELD];
	}

	if (ActSendMailRec.wFieldLen[ACTIONSENDMAIL_CCFIELD]) {
		if (ACTIONSENDMAIL_FLAG_CCFORMULA & ActSendMailRec.dwFlags)
			PrintFormula (p, ActSendMailRec.wFieldLen[ACTIONSENDMAIL_CCFIELD], pScan, "Action Formula::Send Mail::CC");
		else
			PrintText (p, ActSendMailRec.wFieldLen[ACTIONSENDMAIL_CCFIELD], pScan, "Action Text::Send Mail::CC");
		p += ActSendMailRec.wFieldLen[ACTIONSENDMAIL_CCFIELD];
	}

	if (ActSendMailRec.wFieldLen[ACTIONSENDMAIL_BCCFIELD]) {
		if (ACTIONSENDMAIL_FLAG_BCCFORMULA & ActSendMailRec.dwFlags)
			PrintFormula (p, ActSendMailRec.wFieldLen[ACTIONSENDMAIL_BCCFIELD], pScan, "Action Formula::Send Mail::BCC");
		else
			PrintText (p, ActSendMailRec.wFieldLen[ACTIONSENDMAIL_BCCFIELD], pScan, "Action Text::Send Mail::BCC");
		p += ActSendMailRec.wFieldLen[ACTIONSENDMAIL_BCCFIELD];
	}

	if (ActSendMailRec.wFieldLen[ACTIONSENDMAIL_SUBJECTFIELD]) {
		if (ACTIONSENDMAIL_FLAG_SUBJECTFORMULA & ActSendMailRec.dwFlags)
			PrintFormula (p, ActSendMailRec.wFieldLen[ACTIONSENDMAIL_SUBJECTFIELD], pScan, "Action Formula::Send Mail::Subject");
		else
			PrintText (p, ActSendMailRec.wFieldLen[ACTIONSENDMAIL_SUBJECTFIELD], pScan, "Action Text::Send Mail::Subject");
		p += ActSendMailRec.wFieldLen[ACTIONSENDMAIL_SUBJECTFIELD];
	}

	if (ActSendMailRec.wFieldLen[ACTIONSENDMAIL_BODYFIELD]) {
		PrintText (p, ActSendMailRec.wFieldLen[ACTIONSENDMAIL_BODYFIELD], pScan, "Action::Send Mail::Body");
		p += ActSendMailRec.wFieldLen[ACTIONSENDMAIL_BODYFIELD];
	}

    return;
}

/************************************************************************

    FUNCTION:   DumpActionDbcopy

*************************************************************************/
void LNPUBLIC DumpActionDbcopy(char *RecordPtr, DWORD RecordLength, void *pScan) {
    char far *		p = RecordPtr;
    CDACTIONDBCOPY	ActCopyRec;

    NSFAnalyzerEngine::pODSReadMemory (&p, _CDACTIONDBCOPY, &ActCopyRec, 1);
	
	if (ActCopyRec.wServerLen)
		PrintText (p, ActCopyRec.wServerLen, pScan, "Action::DB Copy::Server Name");
	
	if (ActCopyRec.wDatabaseLen)
		PrintText (p, ActCopyRec.wDatabaseLen, pScan, "Action::DB Copy::Database Name");

    return;
}

/************************************************************************

    FUNCTION:   DumpActionDelete

*************************************************************************/
void LNPUBLIC DumpActionDelete(char *RecordPtr, DWORD RecordLength) {
    char far *		p = RecordPtr;
    CDACTIONDELETE	ActDeleteRec;  

    NSFAnalyzerEngine::pODSReadMemory (&p, _CDACTIONDELETE, &ActDeleteRec, 1);

    return;
}

/************************************************************************

    FUNCTION:   DumpActionReadMarks

*************************************************************************/
void LNPUBLIC DumpActionReadMarks(char *RecordPtr, DWORD RecordLength, WORD	RecordType) {
    char far *		p = RecordPtr;
    CDACTIONREADMARKS	ActMarkRec;

	NSFAnalyzerEngine::pODSReadMemory (&p, _CDACTIONREADMARKS, &ActMarkRec, 1);

    return;
}

/************************************************************************

    FUNCTION:   DumpActionByform

*************************************************************************/
void LNPUBLIC DumpActionByform (char *RecordPtr, DWORD RecordLength, void *pScan) {
    char *			p = RecordPtr;
    CDACTIONBYFORM	ActByFormRec;
	WORD			index;

    NSFAnalyzerEngine::pODSReadMemory (&p, _CDACTIONBYFORM, &ActByFormRec, 1);

	for (index = 0; index < ActByFormRec.wFieldCount; index++) {
		DumpODSAssistFieldStruct ( &p, "    ", ActionByFieldOpsTable, pScan);
	}
	
	if (ActByFormRec.wFormNameLen) {
		PrintText (p, ActByFormRec.wFormNameLen, pScan, "Action::By Form::Form Name");
		p += ActByFormRec.wFormNameLen;
	}

	return;
}

/************************************************************************

    FUNCTION:   DumpActionFolder

*************************************************************************/
void LNPUBLIC DumpActionFolder(char *RecordPtr, DWORD RecordLength, WORD RecordType, void *pScan) {
    char far *		p = RecordPtr;
    CDACTIONFOLDER	ActFolderRec;

    NSFAnalyzerEngine::pODSReadMemory (&p, _CDACTIONFOLDER, &ActFolderRec, 1);
	
	if (ActFolderRec.wFolderNameLen)
		PrintText (p, ActFolderRec.wFolderNameLen, pScan, "Action::Folder::Folder Name");

    return;
}

/************************************************************************

    FUNCTION:   DumpActionNewsletter

*************************************************************************/
void LNPUBLIC DumpActionNewsletter(char *RecordPtr, DWORD RecordLength, void *pScan) {
    char far *		p = RecordPtr;
    CDACTIONNEWSLETTER	ActNewsletterRec;

    NSFAnalyzerEngine::pODSReadMemory (&p, _CDACTIONNEWSLETTER, &ActNewsletterRec, 1);

	if (ActNewsletterRec.wViewNameLen) {
		PrintText (p, ActNewsletterRec.wViewNameLen, pScan, "Action::Newsletter::View Name");
		p += ActNewsletterRec.wViewNameLen;
	}

	if (ActNewsletterRec.wFieldLen[ACTIONSENDMAIL_TOFIELD])	{
		if (ACTIONSENDMAIL_FLAG_TOFORMULA & ActNewsletterRec.dwFlags)
			PrintFormula (p, ActNewsletterRec.wFieldLen[ACTIONSENDMAIL_TOFIELD], pScan, "Action Formula::Newsletter::Send Mail::To");
		else
			PrintText (p, ActNewsletterRec.wFieldLen[ACTIONSENDMAIL_TOFIELD], pScan, "Action Text::Newsletter::Send Mail::To");
		p += ActNewsletterRec.wFieldLen[ACTIONSENDMAIL_TOFIELD];
	}

	if (ActNewsletterRec.wFieldLen[ACTIONSENDMAIL_CCFIELD])	{
		if (ACTIONSENDMAIL_FLAG_CCFORMULA & ActNewsletterRec.dwFlags)
			PrintFormula (p, ActNewsletterRec.wFieldLen[ACTIONSENDMAIL_CCFIELD], pScan, "Action Formula::Newsletter::Send Mail::CC");
		else
			PrintText (p, ActNewsletterRec.wFieldLen[ACTIONSENDMAIL_CCFIELD], pScan, "Action Text::Newsletter::Send Mail::CC");
		p += ActNewsletterRec.wFieldLen[ACTIONSENDMAIL_CCFIELD];
	}

	if (ActNewsletterRec.wFieldLen[ACTIONSENDMAIL_BCCFIELD]) {
		if (ACTIONSENDMAIL_FLAG_BCCFORMULA & ActNewsletterRec.dwFlags)
			PrintFormula (p, ActNewsletterRec.wFieldLen[ACTIONSENDMAIL_BCCFIELD], pScan, "Action Formula::Newsletter::Send Mail::BCC");
		else
			PrintText (p, ActNewsletterRec.wFieldLen[ACTIONSENDMAIL_BCCFIELD], pScan, "Action Text::Newsletter::Send Mail::BCC");
		p += ActNewsletterRec.wFieldLen[ACTIONSENDMAIL_BCCFIELD];
	}
	
	if (ActNewsletterRec.wFieldLen[ACTIONSENDMAIL_SUBJECTFIELD]) {
		if (ACTIONSENDMAIL_FLAG_SUBJECTFORMULA & ActNewsletterRec.dwFlags)
			PrintFormula (p, ActNewsletterRec.wFieldLen[ACTIONSENDMAIL_SUBJECTFIELD], "Action Formula::Newsletter::Send Mail::Subject");
		else
			PrintText (p, ActNewsletterRec.wFieldLen[ACTIONSENDMAIL_SUBJECTFIELD], "Action Text::Newsletter::Send Mail::Subject");
		p += ActNewsletterRec.wFieldLen[ACTIONSENDMAIL_SUBJECTFIELD];
	}
	
	if (ActNewsletterRec.wFieldLen[ACTIONSENDMAIL_BODYFIELD]) {
		PrintText (p, ActNewsletterRec.wFieldLen[ACTIONSENDMAIL_BODYFIELD], pScan, "Action::Newsletter::Send Mail::Body");
		p += ActNewsletterRec.wFieldLen[ACTIONSENDMAIL_BODYFIELD];
	}

    return;
}

/************************************************************************

    FUNCTION:   DumpActionRunagent

*************************************************************************/
void LNPUBLIC DumpActionRunagent(char *RecordPtr, DWORD RecordLength, void *pScan) {
    char far *		p = RecordPtr;
    CDACTIONRUNAGENT	ActAgentRec;

    NSFAnalyzerEngine::pODSReadMemory (&p, _CDACTIONRUNAGENT, &ActAgentRec, 1);

	if (ActAgentRec.wAgentNameLen)
		PrintText (p, ActAgentRec.wAgentNameLen, pScan, "Action::Run Agent::Agent Name");

    return;
}

/************************************************************************

    FUNCTION:   DumpActionSenddocument

*************************************************************************/

void LNPUBLIC DumpActionSenddocument(char *	RecordPtr, DWORD RecordLength) {
    char far *		p = RecordPtr;
    CDACTIONSENDDOCUMENT	ActSendDocRec;

    NSFAnalyzerEngine::pODSReadMemory (&p, _CDACTIONSENDDOCUMENT, &ActSendDocRec, 1);

    return;
}

/************************************************************************

    FUNCTION:   DumpActionJavaAgent

*************************************************************************/

void LNPUBLIC DumpActionJavaAgent(char *RecordPtr, DWORD RecordLength, void *pScan) {
    char far			*p = RecordPtr;
    CDACTIONJAVAAGENT	ActJavaAgent;
	OBJECT_DESCRIPTOR  *pObject;
    FILEOBJECT         *pFileObject;
	
	GCHandle _gcHandle = GCHandle::FromIntPtr(safe_cast<IntPtr>(pScan));
	NSFAnalyzerEngine^ scan_engine = safe_cast<NSFAnalyzerEngine^>(_gcHandle.Target);
	
	NSFAnalyzerEngine::pODSReadMemory (&p, _CDACTIONJAVAAGENT, &ActJavaAgent, 1);

	if (0 != ActJavaAgent.wClassNameLen) {
		PrintText (p, ActJavaAgent.wClassNameLen, pScan, "Action::Java Agent::Class Name");
		p += ActJavaAgent.wClassNameLen;
	}

	/* Print the code path string */
	if (0 != ActJavaAgent.wCodePathLen)	{
		PrintText (p, ActJavaAgent.wCodePathLen, pScan, "Action::Java Agent::Code Path");
		p += ActJavaAgent.wCodePathLen;
	}
	
	/* Print the file list string */
	if (0 != ActJavaAgent.wFileListBytes) {
		PrintText (p, ActJavaAgent.wFileListBytes, pScan, "Action::Java Agent::File List");
		p += ActJavaAgent.wFileListBytes;
	}

	pObject = (OBJECT_DESCRIPTOR*)p;
	pFileObject = (FILEOBJECT*)p;
	
	OBJECT_DESCRIPTOR  tempObject;
	OBJECT_DESCRIPTOR *tempPtr;
	tempPtr = pObject;
	NSFAnalyzerEngine::pODSReadMemory( &tempPtr, _OBJECT_DESCRIPTOR, &tempObject, 1 );	
	char retBuffer[256];

	WORD	error;
	BLOCKID bkItem, bkItem2;
	BLOCKID bkField;
	WORD itemLen;
	DWORD fieldLen;

	error = NSFAnalyzerEngine::pNSFItemInfo (
			scan_engine->scanner->CurrentNoteHandle,        
            "$FILE",        
            (WORD)strlen("$FILE"),    
            &bkItem,           
            &itemLen,       
            &bkField,       
            &fieldLen); 

	if (error) {
		if (ERR(error) == ERR_ITEM_NOT_FOUND) {        
			return;
		} else {
			NSFAnalyzerEngine::pOSLoadString(NULLHANDLE, error, retBuffer, 256);
			scan_engine->WriteLog("Unable to view $FILE handle to java source. Noteid: " + scan_engine->scanner->SearchQuery->NoteID + ", Error: "  + gcnew String(retBuffer), true);		
			return;
		}
	}

	error = NSFAnalyzerEngine::pNSFNoteExtractWithCallback(scan_engine->scanner->CurrentNoteHandle, bkItem, NULL, 0, ExtractWithCallback, pScan);
	if (error) {
		NSFAnalyzerEngine::pOSLoadString(NULLHANDLE, error, retBuffer, 256);
		scan_engine->WriteLog("Unable to Extract java source. Noteid: " + scan_engine->scanner->SearchQuery->NoteID + ", Error: "  + gcnew String(retBuffer), true);
		return;
	}

	BLOCKID prevItem = bkItem;
	while (1) {		
		error = NSFAnalyzerEngine::pNSFItemInfoNext(scan_engine->scanner->CurrentNoteHandle, 
								prevItem, 
								"$FILE",  /* name of item we want
												   next; obtain items in
												   in order in note */
								strlen("$FILE"),  /* name length */
								&bkItem2,
								&itemLen,
								&bkField,
								&fieldLen);

		if (ERR(error) == ERR_ITEM_NOT_FOUND) {
			break;
		}
		prevItem = bkItem2;

		if(error = NSFAnalyzerEngine::pNSFNoteExtractWithCallback(scan_engine->scanner->CurrentNoteHandle, bkItem2, NULL, 0, ExtractWithCallback, pScan))
		{
			NSFAnalyzerEngine::pOSLoadString(NULLHANDLE, error, retBuffer, 256);
			scan_engine->WriteLog("Unable to Extract java source. Noteid: " + scan_engine->scanner->SearchQuery->NoteID + ", Error: "  + gcnew String(retBuffer), true);
			return;
		}
	}

	return;
}


STATUS LNCALLBACK ExtractWithCallback(const BYTE *bytes, DWORD length, void far *ptr) {	
	char* cppCode;

	try {
		cli::array<unsigned char, 1>^ byteArray = gcnew cli::array<unsigned char, 1>((int)length);
		for (int i=0; i<(int)length; i++) {
			byteArray[i] = (unsigned char)bytes[i];
		}
			
		System::IO::MemoryStream^ input_ms = gcnew System::IO::MemoryStream(byteArray, 0, (int)length);			
		int size = 2048;
		cli::array<unsigned char, 1>^ data = gcnew cli::array<unsigned char, 1>(2048);
		cli::array<unsigned char, 1>^ data_block = gcnew cli::array<unsigned char, 1>(2048);
		System::IO::MemoryStream^ output_ms = gcnew System::IO::MemoryStream();

		ZipInputStream^ zis = gcnew ZipInputStream(input_ms);
		ZipEntry^ zipEntry;
		try {
			zipEntry = zis->GetNextEntry();
		} catch(Exception^) {
			zis->Close();
			return NOERROR; // sometimes EOF is in header, that is okay
		}

		while (zipEntry) {
			String^ entryFileName = zipEntry->Name;
			while (true) {				
				size = zis->Read(data, 0, data->Length);
				if (size == 0) break;
				output_ms->Write(data, 0, size);
			}
			data_block = output_ms->ToArray();
			String^ content = ::Text::Encoding::ASCII->GetString(data_block);
			cppCode = (char*)Marshal:: StringToHGlobalAnsi(content).ToPointer();	
			PrintText(cppCode, content->Length, ptr, "Java Source File: " + entryFileName);
			zipEntry = zis->GetNextEntry();
		}
					
		zis->Close();

		return NOERROR;
	} catch(Exception^ ex) {
		GCHandle _gcHandle = GCHandle::FromIntPtr(safe_cast<IntPtr>(ptr));
		NSFAnalyzerEngine^ scan_engine = safe_cast<NSFAnalyzerEngine^>(_gcHandle.Target);
		scan_engine->WriteLog(ex->Message + "\n" + ex->StackTrace, true);

		return NOERROR;
	} finally {
		Marshal::FreeHGlobal((IntPtr)cppCode);
	}
}
/************************************************************************

    FUNCTION:   DumpQueryHeader

*************************************************************************/
void DumpQueryHeader(char *RecordPtr, DWORD RecordLength, void *pScan) {
	DumpQueryHeader(RecordPtr, RecordLength, pScan, "Query by Header");
	return;
}

void DumpQueryHeader(char *RecordPtr, DWORD RecordLength, void *pScan, String^ details) {
    char far *		p = RecordPtr;
    CDQUERYHEADER	QHeadRec;

    NSFAnalyzerEngine::pODSReadMemory (&p, _CDQUERYHEADER, &QHeadRec, 1);

	PrintText (p, QHeadRec.Header.Length, pScan, details);
    return;
}

/************************************************************************

    FUNCTION:   DumpQueryTextterm

*************************************************************************/
void DumpQueryTextterm(char *RecordPtr, DWORD RecordLength, void *pScan) {
	DumpQueryTextterm(RecordPtr, RecordLength, pScan, "Query Text Term");
}

void DumpQueryTextterm(char *RecordPtr, DWORD RecordLength, void *pScan, String^ d) {
    char far *		p = RecordPtr;
    CDQUERYTEXTTERM	QTextTermRec;
	int				index;

    NSFAnalyzerEngine::pODSReadMemory (&p, _CDQUERYTEXTTERM, &QTextTermRec, 1);

	for (index = 0; index < MAXTEXTTERMCOUNT; index++) {
		PrintText (p, QTextTermRec.dwLength[index], pScan, d);
		p += QTextTermRec.dwLength[index];
	}

    return;
}

/************************************************************************

    FUNCTION:   DumpQueryByfield

	PURPOSE:	Dump the contents of all the records that share the
				CDQUERYBYFIELD structure - SIG_QUERY_BYFIELD,
				SIG_QUERY_BYDATE, and SIG_QUERY_BYAUTHOR.

*************************************************************************/
void DumpQueryByfield(char *RecordPtr,DWORD RecordLength, WORD	RecordType, void *pScan) {
	DumpQueryByfield(RecordPtr, RecordLength, RecordType, pScan, "Query by Field");
	return;
}
void DumpQueryByfield(char *RecordPtr,DWORD RecordLength, WORD	RecordType, void *pScan, String^ d) {
    char far *		p = RecordPtr;
    CDQUERYBYFIELD	QByFieldRec;

    NSFAnalyzerEngine::pODSReadMemory (&p, _CDQUERYBYFIELD, &QByFieldRec, 1);

	if (QByFieldRec.wFieldNameLen) {
		PrintText (p, QByFieldRec.wFieldNameLen, pScan, d + "::Field Name");
		p += QByFieldRec.wFieldNameLen;
	}

	if (QByFieldRec.wValueLen) {
		PrintCanonicalValue (p, QByFieldRec.wDataType, QByFieldRec.wValueLen, pScan, d + "::Canonical Value");
		p += QByFieldRec.wValueLen;
	}
	
    return;
}

/************************************************************************

    FUNCTION:   DumpQueryFormula

*************************************************************************/
void DumpQueryFormula (char *	RecordPtr, DWORD RecordLength, void *pScan) {
	DumpQueryFormula(RecordPtr, RecordLength, pScan, "Query Formula");
}

void DumpQueryFormula (char *	RecordPtr, DWORD RecordLength, void *pScan, String^ d) {
    char far *		p = RecordPtr;
    CDQUERYFORMULA	QFormulaRec;

    NSFAnalyzerEngine::pODSReadMemory(&p, _CDQUERYFORMULA, &QFormulaRec, 1);
	
	PrintFormula (p, QFormulaRec.wFormulaLen, pScan, d);

    return;
}

/************************************************************************

    FUNCTION:   DumpQueryByform

*************************************************************************/
void DumpQueryByform(char *RecordPtr, DWORD RecordLength, void *pScan) {
	DumpQueryByform(RecordPtr, RecordLength, pScan, "Query By Form");
}

void DumpQueryByform(char *RecordPtr, DWORD RecordLength, void *pScan, String^ d) {
    char *			p = RecordPtr;
    CDQUERYBYFORM	QByFormRec;
	WORD			index;

	NSFAnalyzerEngine::pODSReadMemory (&p, _CDQUERYBYFORM, &QByFormRec, 1);

	for (index = 0; index < QByFormRec.wFieldCount; index++) {		
		DumpODSAssistFieldStruct ( &p, "    ", QueryByFieldOpsTable, pScan);
	}
	
	if (QByFormRec.wFormNameLen) {
		PrintText (p, QByFormRec.wFormNameLen, pScan, d);
		p += QByFormRec.wFormNameLen;
	}


	return;
}

/************************************************************************

    FUNCTION:   DumpQueryByfolder

*************************************************************************/
void DumpQueryByfolder (char *RecordPtr, DWORD RecordLength, void *pScan) {
	DumpQueryByfolder(RecordPtr, RecordLength, pScan, "Query By Folder");
	return;
}
void DumpQueryByfolder (char *RecordPtr, DWORD RecordLength, void *pScan, String^ d) {
    char far *		p = RecordPtr;
    CDQUERYBYFOLDER	QFolderRec;

    NSFAnalyzerEngine::pODSReadMemory (&p, _CDQUERYBYFOLDER, &QFolderRec, 1);

	if (QFolderRec.wFolderNameLen) {
		PrintText (p, QFolderRec.wFolderNameLen, pScan, d);
		p += QFolderRec.wFolderNameLen;
	}

    return;
}

/************************************************************************

    FUNCTION:   DumpQueryUsesform

*************************************************************************/
void DumpQueryUsesform(char *RecordPtr, DWORD RecordLength, void *pScan) {
	DumpQueryUsesform(RecordPtr, RecordLength, pScan, "Query Uses Form");
	return;
}

void DumpQueryUsesform(char *RecordPtr, DWORD RecordLength, void *pScan, String ^d) {
	char *			p = RecordPtr;
    CDQUERYUSESFORM	QUsesFormRec;
	LIST			List;
	USHORT			index;
	char *			pText;
	WORD			textLen;

    NSFAnalyzerEngine::pODSReadMemory (&p, _CDQUERYUSESFORM, &QUsesFormRec, 1);

	// Process the form name list
	NSFAnalyzerEngine::pODSReadMemory (&p, _LIST, ((void *) (&List)), 1);

	pText = p + (List.ListEntries * NSFAnalyzerEngine::pODSLength(_LIST));
	for (index = 0; index < List.ListEntries; index++) {
		NSFAnalyzerEngine::pODSReadMemory (&p, _WORD, ((void *) (&textLen)), 1);		
		PrintText (pText, textLen, pScan, d);
		pText += textLen;
	}

	return;
}

/************************************************************************

    FUNCTION:   DumpQueryTopic

*************************************************************************/
void DumpQueryTopic (char *RecordPtr, DWORD RecordLength) {
	DumpQueryTopic(RecordPtr,RecordLength, "Query Topic");
}

void DumpQueryTopic (char *RecordPtr, DWORD RecordLength, String ^d) {
    char *			p = RecordPtr;
    CDQUERYTOPIC	QTopicRec;

    NSFAnalyzerEngine::pODSReadMemory (&p, _CDQUERYTOPIC, &QTopicRec, 1);
	
    return;
}

/************************************************************************

    FUNCTION:   DumpAgentInfoItem

************************************************************************/
void LNPUBLIC DumpAgentInfoItem(char *Name, WORD NameLength, char *pData, WORD length) {
    return;
}


/************************************************************************

    FUNCTION:   DumpAgentQueryItem

************************************************************************/
void DumpAgentQueryItem (char *  Name, WORD NameLength, char *  pData, WORD length, void *pScan) {	
	DumpAgentQueryItem(Name, NameLength, pData, length, pScan, "Agent Query Item");
	return;
}
void DumpAgentQueryItem (char *  Name, WORD NameLength, char *  pData, WORD length, void *pScan, String^ d) {	
	PrintCompositeBuffer( pData, length, DumpOneAgentQueryRecord, pScan);

    return;
}

/************************************************************************

    FUNCTION:   DumpActionItem

************************************************************************/
void DumpActionItem(char *Name, WORD NameLength, char *pData, WORD length, void *pScan) {
	DumpActionItem(Name, NameLength, pData, length, pScan, String::Empty);

	return;
}
void DumpActionItem(char *Name, WORD NameLength, char *pData, WORD length, void *pScan, String^ details) {	
	PrintCompositeBuffer( pData, length, DumpOneActionRecord, pScan);

    return;
}

/*************************************************************************

    FUNCTION:   PrintNotesActions

    PURPOSE:    Print the Notes action records in the specified buffer.

**************************************************************************/
void PrintNotesActions( char FAR *pBuffer, DWORD BufferLen, void *ptr ) {
	PrintNotesActions(pBuffer, BufferLen, ptr, String::Empty);
}

void PrintNotesActions( char FAR *pBuffer, DWORD BufferLen, void *ptr, String^ details ) {
    WORD    actionType;

    /* Check the data type */
	NSFAnalyzerEngine::pODSReadMemory (&pBuffer, _WORD, &actionType, 1);
    /* Core bug in Notes - the action type word is not */
    /* always being written in canonical order!        */
    /*      if (TYPE_ACTION == actionType)                                  */
    /*      {                                                                                               */
              /* Print the action records */
    DumpActionItem (NULL, 0, pBuffer, ((WORD) (BufferLen - NSFAnalyzerEngine::pODSLength (_WORD))), ptr, details);
    /*      }                                                                                               */
    /*      else                                                                                    */
    /*      {                                                                                               */
    /*              fprintf (dumpfile, "    Unknown action type code: %d (0x%X)\n", */
    /*                      actionType, actionType);                                */
    /*      }                                                                                               */

    return;
}