// Analyze_CAPI.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "analyze.h"

_declspec( dllexport ) HANDLE GetServerList(char *retPort)	
{
	char ports[MAXPORTNAME];
	BOOL status = NOERROR;
	HANDLE serverList;

	status = OSGetEnvironmentString("Ports", ports, MAXPORTNAME);
	if (status == TRUE) 
	{
		//try first port
		for(UINT i=0; i < strlen(ports); i++) 
		{
			if (ports[i] == ',' || ports[i] == '\0') 
			{
				retPort[i] = '\0';
				break;
			}			
			retPort[i] = ports[i];
		}
	}

	status = NSGetServerList((char *)retPort, &serverList);
	
	if (status == NOERROR) 
	{
		return serverList;
	} else 
	{
		return (HANDLE)NULL;
	}
}

_declspec ( dllexport ) WORD GetServerNamesEx(char retServerNames[MAX_SERVERS][MAXPATH])
{
	BOOL status = NOERROR;
	char szLocation[MAXENVVALUE];
	char szPAB[MAXENVVALUE];
	HANDLE db;
	char full_netpath[MAXPATH-1];
	NOTEID view_id;
	HCOLLECTION hCollection;
	COLLECTIONPOSITION pCollPosition;
	HANDLE hBuffer;
	DWORD NumberReturned = 0;
	NOTEID *IdList;
	NOTEHANDLE note;
	char szFieldName[80] = { 0 };
	char szFieldType[80] = { 0 };
	WORD retServerCount = 0;
	bool bUseLocal = false;

	// first, get the name of the current location
	status = OSGetEnvironmentString("Location", szLocation, MAXENVVALUE);
	if (status == TRUE) 
	{
		char *pb = strchr(szLocation, ',');
		if (pb != NULL)
			*pb = 0 ;
	}

	status = OSGetEnvironmentString("MAILSERVER", szPAB, MAXENVVALUE);
	if (status == TRUE) 
	{
		char *pb = strchr(szPAB, ',');
		if (pb != NULL)
			*pb = 0 ;
	}

	if (status = OSPathNetConstruct(NULL, szPAB, _T("names.nsf"), full_netpath))
	{
		printf("unable to open the public NAB %s!!names.nsf\n", szFieldName);
		return 0;
	}

	if (status = NSFDbOpen (full_netpath, &db))
        return 0;

	if (bUseLocal)
	{
		// choose local PAB view
		if (status = NIFFindView(db, _T("Connections"), &view_id))
		{
			NSFDbClose(db);
			return 0;
		}
	} else
	{
		// choose server list from server Directory
		if (status = NIFFindView(db, _T("Servers"), &view_id))
		{
			NSFDbClose(db);
			return 0;
		}
	}

	if (status = NIFOpenCollection( db,	 
									db,	  
		                			view_id,	 
									0,		   
		                			NULLHANDLE,	  
                					&hCollection,	 
		                			NULL,		   
		                			NULL,		
									NULL,	    	
		                			NULL ))	
	{
		NSFDbClose(db);
		return 0;
	}

	pCollPosition.Level = 0;
	pCollPosition.Tumbler[0] = 1;

	 if (status = NIFReadEntries(hCollection,	
							     &pCollPosition,		
							     NAVIGATE_CURRENT,	   
							     1L,		
							     NAVIGATE_NEXT,	   
							     0xFFFFFFFF,		  
							     READ_MASK_NOTEID,	
							     &hBuffer,	  
							     NULL,		 
							     NULL,		 
							     &NumberReturned,	  
							     NULL))		
	 {
		NIFCloseCollection(hCollection);
		NSFDbClose(db);
		return 0;
	 }

	 strcpy_s(retServerNames[retServerCount++], MAXPATH, _T("Local"));
	 if (NumberReturned != 0) 
	 {
		if (hBuffer != NULLHANDLE)
        {
    		IdList = (NOTEID far *)OSLockObject(hBuffer);
    		for (DWORD i=0; i<(DWORD)NumberReturned; i++)
			{
  				if (status = NSFNoteOpen( db, IdList[i], 0, &note))
				{
					// skip categories
				} else
				{
					// scan documents
					WORD lenFieldName = NSFItemGetText(note, 
													  (bUseLocal) ? _T("Destination") : _T("ServerName"), 
													  szFieldName, 
													  sizeof(szFieldName)); 
					strcpy_s(retServerNames[retServerCount++], MAXPATH, szFieldName);
					status = NSFNoteClose(note);
				}
			}
			OSUnlockObject(hBuffer);
            OSMemFree(hBuffer);
		}
	}

	if (status)
	{
		NIFCloseCollection(hCollection);
		NSFDbClose(db);
		return 0;
	}

	if (status = NIFCloseCollection(hCollection))
	{
		NSFDbClose(db);
		return 0;
	}

	if (status = NSFDbClose(db))
		return 0;

	return retServerCount;
}

_declspec ( dllexport ) WORD GetServerNames(HANDLE serverList,
											char retServerNames[MAXPATH][MAXPATH])
{
	char szServerString[MAXPATH]="";
	BYTE far *pServerList;
	WORD wServerCount;
	WORD *pwServerLength;
	BYTE far *pServerName;

	pServerList  = (BYTE far *)OSLockObject(serverList);
	wServerCount = (WORD) *pServerList;
	pwServerLength = (WORD *)(pServerList + sizeof(WORD));
	pServerName = (BYTE far *) pServerList + sizeof(wServerCount) + ((wServerCount) * sizeof(WORD));
	memmove (szServerString, "Local", strlen("Local"));
	szServerString[5] = '\0'; 		
	strcpy_s(retServerNames[0], 6, szServerString);

	for (UINT i=0; i<wServerCount; pServerName+=pwServerLength[i], i++)
	{
		memmove (szServerString, pServerName, pwServerLength[i]);
		szServerString[pwServerLength[i]] = '\0'; 	
		strcpy_s(retServerNames[i+1], MAXPATH, szServerString);
	}
	OSUnlockObject (serverList);
	OSMemFree (serverList);
	
	return wServerCount;
}


_declspec ( dllexport ) WORD GetDatabaseNames(const char *port,
											  const char *serverName,
											  char retDatabaseNames[MAX_ENTRIES][MAXPATH]) 
{	
	STATUS error = NO_ERROR;
    char directory[STRING_LENGTH];   /* directory path */
    char full_netpath[MAXPATH] = ""; /* full network path */
    DBHANDLE    dir_handle;          /* handle for directory */
    
	wDatabaseCount = 0;
	//block = (char**)malloc(MAX_ENTRIES * MAXPATH * sizeof(char*));
	
    strcpy_s(directory, full_netpath);

	if (strcmp(serverName, "Local")) 
	{
		if (error = OSPathNetConstruct(port, 
									   serverName, 
									   directory, 
									   full_netpath))		   
		   return 0;									   
	} else
	{
		if (error = OSPathNetConstruct(NULL, "", directory, full_netpath))
            return 0;
	}
	
	
	if (error = NSFDbOpen (full_netpath, &dir_handle))
	{
        return 0;
	}

	if (error = NSFSearch (
        dir_handle,		       // directory handle
        NULLHANDLE,        // selection formula
        NULL,              // title of view in formula
        SEARCH_FILETYPE +  // search for files
        SEARCH_SUMMARY,    // return a summary buffer
        FILE_DBANY +       // find any .NS? file
        FILE_RECURSE +     // find subdirectories
        FILE_NOUPDIRS,     // don't find the ".." dir					
        NULL,              // starting date
        file_action,       // call for each file found
        NULL,              // argument to action routine
        NULL))             // returned ending date (unused)
	
	if (error = NSFDbClose(dir_handle))
		return 0;

	for (int dbIndex=0; dbIndex<(int)wDatabaseCount; dbIndex++)
	{
		strcpy_s(retDatabaseNames[dbIndex], MAXPATH, dblist[dbIndex]);
		//strcpy_s(retDatabaseNames[dbIndex], MAXPATH, block[dbIndex]);
		//free(block[dbIndex]);
	}
	//free(block);
	return wDatabaseCount;
}

STATUS LNPUBLIC file_action (void *unused, 
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
	item_path = (char *)malloc(MAXPATH*sizeof(char*));
	*item_path = NULL;

	error = NSFGetSummaryValue((ITEM_TABLE *)summary_info, 
						       (char *)_T("$Path"), 
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
	
	
	//block[wDatabaseCount] = (char*)malloc(MAXPATH * sizeof(char *));
	//strcpy_s(block[wDatabaseCount++],MAXPATH, item_path); // push db name into the global array		
	strcpy_s(dblist[wDatabaseCount++],MAXPATH, item_path); 
	free(item_path);	
	
	return NOERROR;
}

_declspec ( dllexport ) WORD GetAbbreviatedCurrentUserName(char *retAbbreviatedName)
{
	char szCurrentUser[MAXUSERNAME+1];
	WORD retLen;
	STATUS error = NOERROR;

	error = SECKFMGetUserName (szCurrentUser);
	if (error != NOERROR) return 0;

	error = DNAbbreviate (0L,                                                
						  NULL,                // user's template   
						  szCurrentUser,       // distinguished name to be abbreviated
						  retAbbreviatedName,  // abbreviated name
						  MAXUSERNAME,         // max output length   
						  &retLen);            // returned output len

	if (error != NOERROR) return 0;

	return retLen;
}

_declspec ( dllexport ) WORD GetCurrentUserMailFileName(char *retMailFile)
{
	BOOL bStatus;
	
	bStatus = OSGetEnvironmentString(_T("MailFile"), 
								     retMailFile, 
									 (WORD)strlen(retMailFile));

	return (WORD)strlen(retMailFile);
}

_declspec ( dllexport ) WORD ATOM_OSLoadString(HMODULE hModule, STATUS error, char *retBuffer, WORD bufferLen) {
	return OSLoadString(hModule, error, retBuffer,  bufferLen);
}

_declspec ( dllexport ) STATUS ATOM_NSFDbOpen(const char *pathName, HANDLE *rethDB)
{
	return NSFDbOpen(pathName, rethDB);
}

_declspec ( dllexport ) STATUS ATOM_NSFDbClose(HANDLE hDB)
{
	return NSFDbClose(hDB);
}

_declspec (dllexport) STATUS ATOM_NSFSearch(HANDLE far hDB,
											HANDLE far hFormula,
											char *ViewTitle,
											WORD SearchFlags,
											WORD NoteClassMask,
											TIMEDATE *Since,
											NSFSEARCHPROC EnumRoutine,
											void *EnumRoutineParameter,
											TIMEDATE *retUntil)
{
	return NSFSearch(hDB, 
					 hFormula, 
					 ViewTitle, 
					 SearchFlags, 
					 NoteClassMask, 
					 Since, 
					 EnumRoutine, 
					 EnumRoutineParameter, 
					 retUntil);
}

_declspec ( dllexport ) STATUS ATOM_NSFNoteOpen (HANDLE hDB, 
												 NOTEID NoteID, 
												 WORD OpenFlags, 
												 HANDLE *rethNote)
{
	return NSFNoteOpen(hDB, NoteID, OpenFlags, rethNote);
}

_declspec ( dllexport ) STATUS ATOM_NSFDbGetNoteInfo (const DBHANDLE hDb, 
													  const NOTEID NoteID,
													  ORIGINATORID far *retNoteOID,
													  TIMEDATE far *retModified,
													  WORD far *retNoteClass)
{
	return NSFDbGetNoteInfo(hDb, NoteID, retNoteOID, retModified, retNoteClass);
}

_declspec ( dllexport ) STATUS ATOM_NSFItemScan(NOTEHANDLE hNote,
												NSFITEMSCANPROC ActionRoutine,
												void *RoutineParameter)
{
	
	return NSFItemScan(hNote, ActionRoutine, RoutineParameter);
}

_declspec ( dllexport ) STATUS ATOM_NSFNoteClose(HANDLE hNote)
{
	return NSFNoteClose(hNote);
}

_declspec ( dllexport ) STATUS ATOM_NSFFormulaDecompile(char far *pFormulaBuffer, 
													   BOOL fSelectionFormula, 
													   HANDLE far *rethFormulaText, 
													   WORD far *retFormulaTextLength)
{
	return NSFFormulaDecompile(pFormulaBuffer, fSelectionFormula, rethFormulaText, retFormulaTextLength);
}

_declspec ( dllexport ) void * ATOM_OSLockObject(HANDLE handle)
{
	return OSLockObject(handle);
}

_declspec ( dllexport ) BOOL ATOM_OSUnlockObject(HANDLE handle)
{
	return OSUnlockObject(handle);
}

_declspec ( dllexport ) STATUS ATOM_OSMemFree(HANDLE handle)
{
	return OSMemFree(handle);
}

_declspec ( dllexport ) void ATOM_ODSReadMemory(void *ppSrc, 
										   WORD type, 
										   void *pDest, 
										   WORD iterations)
{	
	return ODSReadMemory(ppSrc, type, pDest, iterations);
}

_declspec ( dllexport ) STATUS ATOM_ListGetText (void *pList,
												 BOOL fPrefixDataType,
												 WORD EntryNumber,
												 char **retTextPointer,
												 WORD *retTextLength)
{
	return ListGetText(pList, fPrefixDataType, EntryNumber, retTextPointer, retTextLength);
}

_declspec ( dllexport ) STATUS ATOM_ConvertTIMEDATEToText (void *IntlFormat,
														   TFMT *TextFormat,
														   TIMEDATE *InputTime,
														   char *retTextBuffer,
														   WORD TextBufferLength,
														   WORD  *retTextLength)
{
	return ConvertTIMEDATEToText(IntlFormat, TextFormat, InputTime, retTextBuffer, TextBufferLength, retTextLength);
}

_declspec ( dllexport ) WORD ATOM_ODSLength(WORD type)
{
	return ODSLength(type);
}

_declspec ( dllexport ) STATUS ATOM_OSPathNetConstruct(const char *PortName,
													   const char *ServerName,
													   const char *FileName,
													   char retPathName[MAXPATH])
{
	return OSPathNetConstruct(PortName, ServerName, FileName, retPathName);
}

_declspec (dllexport ) STATUS ATOM_NSFDbPathGet(DBHANDLE hDB,
												char *retCanonicalPathName,
												char *retExpandedPathName)
{ 
	return NSFDbPathGet(hDB, retCanonicalPathName, retExpandedPathName);
}

_declspec (dllexport ) WORD ATOM_NSFItemGetText(NOTEHANDLE note_handle,
												const char *item_name,
												char *item_text,
												WORD text_len)
{
	return NSFItemGetText(note_handle, item_name, item_text, text_len);
}

_declspec ( dllexport ) void ATOM_OSCurrentTIMEDATE(TIMEDATE *retTimeDate)
{
	OSCurrentTIMEDATE(retTimeDate);
	return;
}

_declspec ( dllexport ) void ATOM_NSFNoteGetInfo(NOTEHANDLE note_handle,
												 WORD note_member,
												 void *value_ptr)
{
	NSFNoteGetInfo(note_handle, note_member, value_ptr);
	return;
}

_declspec ( dllexport ) STATUS ATOM_NSFDbReplicaInfoGet(DBHANDLE hDb,
														DBREPLICAINFO *retReplicationInfo)
{
	return (NSFDbReplicaInfoGet(hDb, retReplicationInfo));
}

_declspec ( dllexport ) STATUS ATOM_NSFDbInfoGet(DBHANDLE hDb, char retBuffer[NSF_INFO_SIZE])
{
	return (NSFDbInfoGet(hDb, retBuffer));
}

_declspec ( dllexport ) void ATOM_NSFDbInfoParse(char far *Info, WORD  What, char Buffer[NSF_INFO_SIZE], WORD  Length)
{
	NSFDbInfoParse(Info, What, Buffer, Length);
}

_declspec( dllexport ) BOOL ATOM_NSFGetSummaryValue(const void *summary_buffer_ptr, const char *text_item_name, char *text_item_value, WORD max_buffer_len) {
	return NSFGetSummaryValue(summary_buffer_ptr, text_item_name, text_item_value, max_buffer_len);	
}

_declspec( dllexport ) STATUS ATOM_NSFDbReadObject(DBHANDLE hDB, DWORD ObjectID, DWORD Offset, DWORD Length, HANDLE *rethBuffer) {
	return NSFDbReadObject(hDB, ObjectID, Offset, Length, (HANDLE*)*rethBuffer);	
}

_declspec( dllexport ) STATUS ATOM_NSFDbFreeObject(DBHANDLE hDB, DWORD ObjectID) {
	return NSFDbFreeObject(hDB, ObjectID);
}

_declspec( dllexport ) STATUS ATOM_NSFItemInfo(NOTEHANDLE note_handle, 
											   const char far *item_name, 
											   WORD  name_len,
											   BLOCKID far *item_blockid, 
											   WORD far *value_datatype, 
											   BLOCKID far *value_blockid, 
											   DWORD far *value_len) {

	return NSFItemInfo(note_handle, item_name, name_len, item_blockid, value_datatype, value_blockid, value_len);
}

_declspec( dllexport ) STATUS ATOM_NSFNoteExtractWithCallback(NOTEHANDLE  hNote,
															  BLOCKID  bhItem, 
															  ENCRYPTION_KEY far *DecryptionKey,
															  WORD wFlags, 
															  NOTEEXTRACTCALLBACK  pNoteExtractCallback,
															  void far *pParam) {

	return NSFNoteExtractWithCallback(hNote, bhItem, DecryptionKey, wFlags, pNoteExtractCallback, pParam);
}

_declspec( dllexport ) STATUS ATOM_NSFItemInfoNext(NOTEHANDLE note_handle, 
												   BLOCKID  nextItem, 
												   const char far *item_name, 
											       WORD  name_len,
											       BLOCKID far *item_blockid, 
											       WORD far *value_datatype, 
											       BLOCKID far *value_blockid, 
											       DWORD far *value_len) {

	return NSFItemInfoNext(note_handle, nextItem, item_name, name_len, item_blockid, value_datatype, value_blockid, value_len);
}

_declspec ( dllexport) void ThreadInitialize() {
	NotesInitExtended((int)0, (char**)NULL);
}
_declspec ( dllexport) void ThreadTerminate() {
	NotesTerm();
}