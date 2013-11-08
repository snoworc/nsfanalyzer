#pragma once

#include <lapiplat.h>
#include <osenv.h>
#include <ns.h>
#include <osmem.h>
#include <nsfsearc.h>
#include <osfile.h>
#include <nsfdb.h>
#include <osmisc.h>
#include <names.h>
#include <nsferr.h>
#include <textlist.h>
#include <ods.h>
#include <odstypes.h>
#include <nsfnote.h>
#include <kfm.h>
#include <dname.h>
#include <ostime.h>
#include <nif.h>
#include <nsfobjec.h>
#include <stdio.h>
#include <malloc.h>

#define MAX_ENTRIES 3000
#define MAX_SERVERS 200
#define STRING_LENGTH  256

// forward declarations
STATUS LNPUBLIC		file_action (void *, SEARCH_MATCH far *, ITEM_TABLE *);
STATUS LNPUBLIC		file_actionEx (void *, SEARCH_MATCH far *, ITEM_TABLE *);

// global vars
WORD wDatabaseCount;
char dblist[MAX_ENTRIES][MAXPATH];

extern "C" 
{
	extern __declspec( dllexport ) HANDLE	GetServerList		(char *);

	extern __declspec( dllexport ) WORD		GetServerNamesEx(char [MAX_SERVERS][MAXPATH]);

	extern __declspec( dllexport ) WORD		GetServerNames	(HANDLE,
													         char [MAXPATH][MAXPATH]);
	
	extern __declspec( dllexport ) WORD	  GetDatabaseNames	(const char *,
															 const char *,
														     char [MAX_ENTRIES][MAXPATH]);
		
	extern __declspec( dllexport ) WORD	  GetAbbreviatedCurrentUserName(char *);

	extern __declspec( dllexport ) WORD   GetCurrentUserMailFileName(char *);

	extern __declspec( dllexport)WORD ATOM_OSLoadString(HMODULE, STATUS, char *, WORD);

	extern __declspec( dllexport ) STATUS ATOM_NSFDbOpen(const char *, HANDLE *);

	extern __declspec( dllexport ) STATUS ATOM_NSFDbClose(HANDLE);

	extern __declspec( dllexport) STATUS ATOM_NSFSearch(HANDLE far,
													   HANDLE far,
													   char *,
											           WORD,
											           WORD,
											           TIMEDATE *,
											           NSFSEARCHPROC,
											           void *,
											           TIMEDATE *);


	extern __declspec( dllexport ) STATUS ATOM_NSFNoteOpen (HANDLE, 
														    NOTEID, 
															WORD, 
															HANDLE *);

	extern __declspec( dllexport ) STATUS ATOM_NSFDbGetNoteInfo (const DBHANDLE,
																 const NOTEID, 
																 ORIGINATORID far *, 
																 TIMEDATE far *, 
																 WORD far *);

	extern __declspec ( dllexport ) STATUS ATOM_NSFItemScan(NOTEHANDLE,
															NSFITEMSCANPROC,
															void *);

	extern __declspec( dllexport ) STATUS ATOM_NSFNoteClose(HANDLE);

	extern __declspec( dllexport ) STATUS ATOM_NSFFormulaDecompile(char far *, 
																   BOOL, 
																   HANDLE far *, 
																   WORD far *);

	extern __declspec( dllexport ) void * ATOM_OSLockObject(HANDLE);

	extern __declspec( dllexport ) BOOL ATOM_OSUnlockObject(HANDLE);

	extern __declspec( dllexport ) STATUS ATOM_OSMemFree(HANDLE);

	extern __declspec( dllexport ) void ATOM_ODSReadMemory(void *, 
														   WORD, 
										                   void *, 
										                   WORD);

	extern __declspec( dllexport ) STATUS ATOM_ListGetText (void *,
															BOOL,
															WORD,
															char **,
															WORD *);

	extern __declspec( dllexport ) STATUS ATOM_ConvertTIMEDATEToText (void *,
																	  TFMT *,
																	  TIMEDATE *,
																	  char *,
																	  WORD,
																	  WORD *);

	extern __declspec( dllexport ) WORD ATOM_ODSLength(WORD);

	extern __declspec( dllexport ) STATUS ATOM_OSPathNetConstruct(const char *,
																  const char *,
																  const char *,
																  char x[MAXPATH]);

	extern __declspec( dllexport ) STATUS ATOM_NSFDbPathGet(DBHANDLE,
															char *,
															char *);

	extern __declspec( dllexport ) WORD ATOM_NSFItemGetText(NOTEHANDLE, 
															const char *, 
															char *, 
															WORD);

	extern __declspec( dllexport ) void ATOM_OSCurrentTIMEDATE(TIMEDATE *);

	extern __declspec( dllexport ) void ATOM_NSFNoteGetInfo(NOTEHANDLE, 
															WORD, 
															void*);
	
	extern __declspec( dllexport ) STATUS ATOM_NSFDbReplicaInfoGet(DBHANDLE, DBREPLICAINFO *);

	extern __declspec( dllexport ) STATUS ATOM_NSFDbInfoGet(DBHANDLE, char x[NSF_INFO_SIZE]);
	
	extern __declspec( dllexport ) void ATOM_NSFDbInfoParse(char far *, WORD, char x[NSF_INFO_SIZE], WORD);
	
	extern __declspec( dllexport ) BOOL ATOM_NSFGetSummaryValue(const void *, const char *, char *, WORD);

	extern __declspec( dllexport ) STATUS ATOM_NSFDbReadObject(DBHANDLE,DWORD,DWORD,DWORD,HANDLE *);

	extern __declspec( dllexport ) STATUS ATOM_NSFDbFreeObject(DBHANDLE,DWORD);

	extern __declspec( dllexport ) STATUS ATOM_NSFItemInfo(NOTEHANDLE, const char *, WORD, BLOCKID *, WORD *, BLOCKID *, DWORD *);

	extern __declspec( dllexport ) STATUS ATOM_NSFNoteExtractWithCallback(NOTEHANDLE, BLOCKID, ENCRYPTION_KEY *, WORD, NOTEEXTRACTCALLBACK, void *);

	extern __declspec( dllexport ) STATUS ATOM_NSFItemInfoNext(NOTEHANDLE, BLOCKID, const char *, WORD, BLOCKID *, WORD *, BLOCKID *, DWORD *);

	extern _declspec ( dllexport ) void ThreadInitialize();

	extern _declspec ( dllexport ) void ThreadTerminate();
}
