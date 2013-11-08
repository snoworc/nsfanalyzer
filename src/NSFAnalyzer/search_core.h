#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace System;
using namespace System::Windows::Forms;
#include "Configuration.h"
#include "NoteClassTable.h"
#include "resource.h"
#include "ScanIterator.h"

#define THREAD_CANCEL			777
#define MAX_ENTRIES				3000
#define MAX_SERVERS				200
#define LITERAL_TABLE_END       (0xFFFFFFFF)

// extern func declarations
typedef WORD	( *AUXGetServerNamesEx)(char [MAX_SERVERS][MAXPATH]);
typedef WORD	( *AUXGetDatabaseNames)(char *, char *, char [MAX_ENTRIES][MAXPATH]);
typedef WORD	( *AUXOSLoadString)(HMODULE, STATUS, char *, WORD);
typedef STATUS	( *AUXNSFDbOpen)(const char *, DHANDLE*);
typedef STATUS	( *AUXNSFDbClose)(HANDLE);
typedef STATUS	( *AUXNSFSearch)(HANDLE, HANDLE, char *, WORD, WORD, TIMEDATE *, NSFSEARCHPROC, void *, TIMEDATE *);
typedef STATUS	( *AUXNSFNoteOpen)(HANDLE, NOTEID, WORD, HANDLE *);
typedef STATUS	( *AUXNSFDbGetNoteInfo)(const DBHANDLE, const NOTEID, ORIGINATORID *, TIMEDATE *, WORD *);
typedef STATUS  ( *AUXNSFItemScan)(NOTEHANDLE, NSFITEMSCANPROC, void *);
typedef STATUS	( *AUXNSFNoteClose)(HANDLE);
typedef STATUS	( *AUXNSFFormulaDecompile)(char far *, BOOL, HANDLE far *, WORD far *);
typedef void*	( *AUXOSLockObject)(HANDLE);
typedef BOOL	( *AUXOSUnlockObject)(HANDLE);
typedef STATUS	( *AUXOSMemFree)(HANDLE);
typedef void	( *AUXODSReadMemory)(void *, WORD, void *, WORD);
typedef STATUS	( *AUXListGetText)(void *, BOOL, WORD, char **, WORD *);
typedef STATUS	( *AUXConvertTIMEDATEToText)(void *, TFMT *, TIMEDATE *, char *, WORD, WORD *);
typedef WORD	( *AUXODSLength)(WORD);
typedef STATUS	( *AUXOSPathNetConstruct)(const char *, const char *, const char *, char *);
typedef STATUS  ( *AUXNSFDbPathGet)(DBHANDLE, char *, char *);
typedef WORD	( *AUXNSFItemGetText)(NOTEHANDLE, const char *, char *, WORD);
typedef void	( *AUXOSCurrentTIMEDATE)(TIMEDATE *);
typedef void	( *AUXNSFNoteGetInfo)(NOTEHANDLE, WORD, void *);
typedef STATUS	( *AUXNSFDbReplicaInfoGet)(DBHANDLE, DBREPLICAINFO *);
typedef STATUS  ( *AUXNSFDbInfoGet)(DBHANDLE, char *);
typedef void	( *AUXNSFDbInfoParse)(char far *, WORD, char *, WORD);
typedef BOOL	( *AUXNSFGetSummaryValue)(const void far *, const char *, char *, WORD);
typedef STATUS  ( *AUXNSFDbReadObject)(DBHANDLE, DWORD, DWORD, DWORD, HANDLE *);
typedef STATUS  ( *AUXNSFDbFreeObject)(DBHANDLE, DWORD);
typedef STATUS  ( *AUXNSFItemInfo)(NOTEHANDLE, const char *, WORD, BLOCKID *, WORD *, BLOCKID *, DWORD *);
typedef STATUS  ( *AUXNSFNoteExtractWithCallback)(NOTEHANDLE, BLOCKID, ENCRYPTION_KEY *, WORD, NOTEEXTRACTCALLBACK, void *);
typedef STATUS  ( *AUXNSFItemInfoNext)(NOTEHANDLE, BLOCKID, const char *, WORD, BLOCKID *, WORD *, BLOCKID *, DWORD *);
typedef void	( *AUXThreadInitialize)();
typedef void	( *AUXThreadTerminate)();

typedef struct
{
	DWORD           dwValue;
	char *          pName;
} LITERAL_NAME_ENTRY;
STATUS LNPUBLIC BuildDbList( void far *, SEARCH_MATCH far *, ITEM_TABLE far *);
STATUS LNPUBLIC ScanNote( void far *, SEARCH_MATCH far *, ITEM_TABLE far *);
STATUS LNPUBLIC ScanItem(WORD, WORD, char far *, WORD, VOID far *, DWORD, void far *);
bool IsItemName(void far *, String^);
char * LNPUBLIC GetLiteralString (LITERAL_NAME_ENTRY *, DWORD);
void searchBuffer(char *, void *);
void searchBuffer(char *, void *, String^);
void PrintText( char far *, DWORD, void *);
void PrintText( char far *, DWORD, void *, String^);
void PrintFormula (char far *, WORD, void *);
void PrintFormula (char far *, WORD, void *, String^);
void DumpLotusScriptObjectItem (char *, WORD, char *, WORD, void *);
void DumpLotusScriptObjectItem (char *, WORD, char *, WORD, void *, String^);
void LNPUBLIC PrintNOTELINK(NOTELINK *, void *);
void LNPUBLIC PrintUNID (UNID *, void *);
void DumpHTMLItem(char *, WORD, char *, WORD, void *);
void DumpHTMLItem(char *, WORD, char *, WORD, void *, String^);
void PrintScriptSource (char far *, DWORD, void *);
void PrintScriptSource (char far *, DWORD, void *, String^);
void DumpAgentQueryItem (char * , WORD, char * , WORD, void *);
void DumpAgentQueryItem (char * , WORD, char * , WORD, void *, String^);
void LNPUBLIC DumpAgentInfoItem(char *, WORD, char *, WORD);
STATUS LNPUBLIC PrintCompositeBuffer (char FAR *, DWORD, ActionRoutinePtr, void *);
void LNPUBLIC GetTDString(TIMEDATE *, char *);
void PrintCanonicalValue (char *, WORD, WORD, void *);
void PrintCanonicalValue (char *, WORD, WORD, void *, String^);
STATUS LNPUBLIC DumpOneAgentQueryRecord(char *, WORD, DWORD, void * );
STATUS LNPUBLIC DumpOneActionRecord(char *, WORD, DWORD, void *);
STATUS LNCALLBACK ExtractWithCallback(const BYTE *, DWORD, void far *);
void LNPUBLIC DumpActionHeader(char *, DWORD);
void LNPUBLIC DumpActionModifyfield (char *, DWORD, void *);
void LNPUBLIC DumpActionReply(char *, DWORD, void *);
void LNPUBLIC DumpActionFormula(char *, DWORD, WORD, void *);
void LNPUBLIC DumpActionLotusscript(char *, DWORD, void *);
void LNPUBLIC DumpActionSendmail(char *, DWORD, void *);
void LNPUBLIC DumpActionDbcopy(char *, DWORD, void *);
void LNPUBLIC DumpActionDelete(char *, DWORD);
void LNPUBLIC DumpActionReadMarks(char *, DWORD, WORD);
void LNPUBLIC DumpActionByform (char *, DWORD, void *);
void LNPUBLIC DumpActionFolder(char *, DWORD, WORD, void *);
void LNPUBLIC DumpActionNewsletter(char *, DWORD, void *);
void LNPUBLIC DumpActionSenddocument(char *, DWORD);
void LNPUBLIC DumpActionJavaAgent(char *, DWORD, void *);
void LNPUBLIC DumpActionRunagent(char *, DWORD, void *);
void DumpQueryHeader(char *, DWORD, void *);
void DumpQueryHeader(char *, DWORD, void *, String^);
void DumpQueryTextterm(char *, DWORD, void *);
void DumpQueryTextterm(char *, DWORD, void *, String^);
void DumpQueryByfield(char *,DWORD, WORD, void *);
void DumpQueryByfield(char *,DWORD, WORD, void *, String^);
void DumpQueryFormula (char *, DWORD, void *);
void DumpQueryFormula (char *, DWORD, void *, String^);
void DumpQueryByform(char *, DWORD, void *);
void DumpQueryByform(char *, DWORD, void *, String^);
void DumpQueryByfolder (char *, DWORD, void *); 
void DumpQueryByfolder (char *, DWORD, void *, String^); 
void DumpQueryUsesform(char *, DWORD, void *);
void DumpQueryUsesform(char *, DWORD, void *, String^);
void DumpQueryTopic(char *, DWORD);
void DumpQueryTopic(char *, DWORD, String^);
void DumpActionItem(char *, WORD, char *, WORD, void *);
void DumpActionItem(char *, WORD, char *, WORD, void *, String^);
void NSFDDUMPDumpMemory(char *, WORD, void *);
void NSFDDUMPDumpMemory(char *, WORD, void *, String^);
void LNPUBLIC DumpODSAssistFieldStruct (char **, char *, LITERAL_NAME_ENTRY *, void *);
void PickApartTime (DWORD, WORD *, WORD *, WORD *, WORD *);
void LNPUBLIC DumpTextlistItem(char *, WORD, void *);
void LNPUBLIC DumpNumberItem(char *, WORD);
void LNPUBLIC DumpNumberRangeItem(char *, WORD);
void LNPUBLIC DumpTimeItem(char *, WORD);
void LNPUBLIC DumpTimeRangeItem(char *, WORD);
void PrintNotesActions( char FAR *, DWORD, void *);
void PrintNotesActions( char FAR *, DWORD, void *, String^);
void LNPUBLIC DumpCDParagraph(char *, DWORD, void *);
void LNPUBLIC DumpCDText(char *RecordPtr, DWORD, WORD, void *);
void LNPUBLIC DumpCDHeader(char *, DWORD, void *);
void LNPUBLIC DumpCDLinkexport2(char *RecordPtr, DWORD, void *);
void LNPUBLIC DumpCDBitmapsegment(char *, DWORD, void *);
void LNPUBLIC DumpCDColortable(char *, DWORD, void *);
void LNPUBLIC DumpCDField( char *, DWORD, WORD, void *);
void LNPUBLIC DumpCDDocument(char *, DWORD, void *);
void LNPUBLIC DumpCDLink2( char *, DWORD, void *);
void LNPUBLIC DumpCDPatterntable(char *, DWORD, void *);
void LNPUBLIC DumpCDOlebegin(char *, DWORD, void *);
void LNPUBLIC DumpCDHotspotbegin(char *, DWORD, WORD, void *);
void LNPUBLIC DumpCDBar(char *, DWORD, void *);
void LNPUBLIC DumpCDAction(char *, DWORD, void *);
STATUS LNPUBLIC DumpOneCDRecord(char *, WORD, DWORD, void *);
void LNPUBLIC DumpCDPmmetaseg(char *, DWORD, void *);
void LNPUBLIC DumpCDWinmetaseg(char *, DWORD, void *);
void LNPUBLIC DumpCDMacmetaseg(char *, DWORD, void *);
void LNPUBLIC DumpCDCgmmeta(char *, DWORD, void *);
void LNPUBLIC DumpCompoundTextItem(char *, WORD, char *, WORD, void *);
void LNPUBLIC DumpCDStylename(char * RecordPtr, DWORD, void *);
void LNPUBLIC DumpCDButton(char *, DWORD, void *);
void LNPUBLIC DumpCDAltText (char *, DWORD, WORD, void *);
void LNPUBLIC DumpCDExtfield(char *, DWORD, void *);
void LNPUBLIC DumpActiveObject (char *, DWORD, void *);
void LNPUBLIC DumpHSOleRichText(char *, DWORD, void *);
void LNPUBLIC DumpActiveObjectParameter (int, char **, void *);
void LNPUBLIC DumpActiveObjectLink (int, char **, void *);
void LNPUBLIC DumpCDPabhide(char *, DWORD, void *);
void LNPUBLIC DumpCDTextEffect(char *, DWORD, WORD, void *);
void LNPUBLIC DumpCDTransparentTable(char *, DWORD, void *);
void LNPUBLIC DumpCDStorageLink(char *, DWORD, void *);
void LNPUBLIC DumpCDDocautolaunch(char *, DWORD, void *);
void LNPUBLIC DumpCDOleObjInfo( char *, DWORD, void *);
void LNPUBLIC DumpCDAnchor(char *, DWORD, void *);
void LNPUBLIC DumpCDHtmlFormula (char *, DWORD, void *);
void LNPUBLIC DumpCDHtmlSegment (char *, DWORD, void *);
void LNPUBLIC DumpCDEmbeddedOutline (char *, DWORD, void *);
void LNPUBLIC DumpCDEmbeddedView(char *, DWORD, void *);
void LNPUBLIC DumpCDTarget(char *, DWORD, void *);
void LNPUBLIC DumpCDMapElement(char *, DWORD, void *);
void LNPUBLIC DumpCDResource(char *, DWORD, WORD, void *);
void LNPUBLIC DumpCDEvent(char *, DWORD, WORD, void *);
void LNPUBLIC DumpCDIDName(char *, DWORD, WORD, void *);
void LNPUBLIC DumpCDPreTableBegin(char *, DWORD, void *);
void LNPUBLIC DumpCDEmbeddedSchedCtl(char *, DWORD, void *);
void LNPUBLIC DumpCDBlobPart(char *, DWORD, WORD, void *);
void LNPUBLIC DumpCDCaption(char *, DWORD, void *);
void LNPUBLIC DumpCDFrame(char *, DWORD, void *);
void LNPUBLIC DumpCDActionExt(char *, DWORD, void *);
void LNPUBLIC DumpCDEmbeddedSchedCtlExtra(char *, DWORD, void *);
void LNPUBLIC DumpCDEmbeddedCalCtl(char *, DWORD, void *);
void LNPUBLIC DumpCDFileHeader(char *, DWORD, void *) ;
void LNPUBLIC DumpCDDECSField(char *, DWORD, void *);
void LNPUBLIC DumpCDEmbeddedEditCtl(char *, DWORD, void *);
void LNPUBLIC DumpCDFieldHint(char *, DWORD, void *);
void LNPUBLIC DumpCDEmbedExtraInfo(char *,	DWORD, void *);

#define NO_MATCH		0
#define EXACT_MATCH		1
#define POSSIBLE_MATCH  2

static LITERAL_NAME_ENTRY TypeStringTable [] =
{
	{TYPE_ERROR,				"TYPE_ERROR"},
	{TYPE_UNAVAILABLE,			"TYPE_UNAVAILABLE"},
	{TYPE_TEXT,					"TYPE_TEXT"},
	{TYPE_TEXT_LIST,			"TYPE_TEXT_LIST"},
	{TYPE_NUMBER,				"TYPE_NUMBER"},
	{TYPE_NUMBER_RANGE,			"TYPE_NUMBER_RANGE"},
	{TYPE_TIME,					"TYPE_TIME"},
	{TYPE_TIME_RANGE,			"TYPE_TIME_RANGE"},
	{TYPE_FORMULA,				"TYPE_FORMULA"},
	{TYPE_USERID,				"TYPE_USERID"},
	{TYPE_INVALID_OR_UNKNOWN,	"TYPE_INVALID_OR_UNKNOWN"},
	{TYPE_COMPOSITE,			"TYPE_COMPOSITE"},
	{TYPE_COLLATION,			"TYPE_COLLATION"},
	{TYPE_OBJECT,				"TYPE_OBJECT"},
	{TYPE_NOTEREF_LIST,			"TYPE_NOTEREF_LIST"},
	{TYPE_VIEW_FORMAT,			"TYPE_VIEW_FORMAT"},
	{TYPE_ICON,					"TYPE_ICON"},
	{TYPE_NOTELINK_LIST,		"TYPE_NOTELINK_LIST"},
	{TYPE_SIGNATURE,			"TYPE_SIGNATURE"},
	{TYPE_SEAL,					"TYPE_SEAL"},
	{TYPE_SEALDATA,				"TYPE_SEALDATA"},
	{TYPE_SEAL_LIST,			"TYPE_SEAL_LIST"},
	{TYPE_HIGHLIGHTS,			"TYPE_HIGHLIGHTS"},
	{TYPE_WORKSHEET_DATA,		"TYPE_WORKSHEET_DATA"},
	{TYPE_USERDATA,				"TYPE_USERDATA"},
	{TYPE_QUERY,				"TYPE_QUERY"},
	{TYPE_ACTION,				"TYPE_ACTION"},
	{TYPE_ASSISTANT_INFO,		"TYPE_ASSISTANT_INFO"},
	{TYPE_VIEWMAP_DATASET,		"TYPE_VIEWMAP_DATASET"},
	{TYPE_VIEWMAP_LAYOUT,		"TYPE_VIEWMAP_LAYOUT"},
	{TYPE_LSOBJECT,				"TYPE_LSOBJECT"},
	{TYPE_HTML,					"TYPE_HTML"},

		/* This must be the last entry! */
	{LITERAL_TABLE_END,			"UNKNOWN DATA TYPE"}
};

static LITERAL_NAME_ENTRY		*TypeStringTablePtr = TypeStringTable;

/* QueryByField operators */
static LITERAL_NAME_ENTRY QueryByFieldOpsTable [] =
{
	{QUERYBYFIELD_OP_GREATER,		"QUERYBYFIELD_OP_GREATER"},
	{QUERYBYFIELD_OP_LESS,			"QUERYBYFIELD_OP_LESS"},
	{QUERYBYFIELD_OP_NOTEQUAL,		"QUERYBYFIELD_OP_NOTEQUAL"},
	{QUERYBYFIELD_OP_BETWEEN,		"QUERYBYFIELD_OP_BETWEEN"},
	{QUERYBYFIELD_OP_NOTWITHIN,		"QUERYBYFIELD_OP_NOTWITHIN"},
	{QUERYBYFIELD_OP_EQUAL,			"QUERYBYFIELD_OP_EQUAL"},
	{QUERYBYFIELD_OP_CONTAINS,		"QUERYBYFIELD_OP_CONTAINS"},
	{QUERYBYFIELD_OP_INTHELAST,		"QUERYBYFIELD_OP_INTHELAST"},
	{QUERYBYFIELD_OP_INTHENEXT,		"QUERYBYFIELD_OP_INTHENEXT"},
	{QUERYBYFIELD_OP_OLDERTHAN,		"QUERYBYFIELD_OP_OLDERTHAN"},
	{QUERYBYFIELD_OP_DUEIN,			"QUERYBYFIELD_OP_DUEIN"},
	{QUERYBYFIELD_OP_DOESNOTCONTAIN, "QUERYBYFIELD_OP_DOESNOTCONTAIN"},

		/* This must be the last entry! */
	{LITERAL_TABLE_END,				"UNKNOWN OPERATOR"}
};

	/* QueryByField operators */
static LITERAL_NAME_ENTRY ActionByFieldOpsTable [] =
{
	{ACTIONBYFIELD_OP_REPLACE,		"ACTIONBYFIELD_OP_REPLACE"},
	{ACTIONBYFIELD_OP_APPEND,		"ACTIONBYFIELD_OP_APPEND"},
	{ACTIONBYFIELD_OP_REMOVE,		"ACTIONBYFIELD_OP_REMOVE"},

		/* This must be the last entry! */
	{LITERAL_TABLE_END,				"UNKNOWN OPERATOR"}
};

/*
 *  AssistTriggerTypeTable - used by GetLiteralString()
 */

static LITERAL_NAME_ENTRY AssistTriggerTypeTable [] =
{
	{ASSISTTRIGGER_TYPE_NONE,		"ASSISTTRIGGER_TYPE_NONE"},
	{ASSISTTRIGGER_TYPE_SCHEDULED,	"ASSISTTRIGGER_TYPE_SCHEDULED"},
	{ASSISTTRIGGER_TYPE_NEWMAIL,	"ASSISTTRIGGER_TYPE_NEWMAIL"},
	{ASSISTTRIGGER_TYPE_PASTED,		"ASSISTTRIGGER_TYPE_PASTED"},
	{ASSISTTRIGGER_TYPE_MANUAL,		"ASSISTTRIGGER_TYPE_MANUAL"},
	{ASSISTTRIGGER_TYPE_DOCUPDATE,	"ASSISTTRIGGER_TYPE_DOCUPDATE"},

		/* This must be the last entry! */
	{LITERAL_TABLE_END,		"UNKNOWN TRIGGER TYPE"}
};

/*
 *  AssistSearchTypeTable - used by GetLiteralString()
 */

static LITERAL_NAME_ENTRY AssistSearchTypeTable [] =
{
	{ASSISTSEARCH_TYPE_NONE,		"ASSISTSEARCH_TYPE_NONE"},
	{ASSISTSEARCH_TYPE_ALL,			"ASSISTSEARCH_TYPE_ALL"},
	{ASSISTSEARCH_TYPE_NEW,			"ASSISTSEARCH_TYPE_NEW"},
	{ASSISTSEARCH_TYPE_MODIFIED,	"ASSISTSEARCH_TYPE_MODIFIED"},
	{ASSISTSEARCH_TYPE_SELECTED,	"ASSISTSEARCH_TYPE_SELECTED"},
	{ASSISTSEARCH_TYPE_VIEW,		"ASSISTSEARCH_TYPE_VIEW"},
	{ASSISTSEARCH_TYPE_UNREAD,		"ASSISTSEARCH_TYPE_UNREAD"},
	{ASSISTSEARCH_TYPE_PROMPT,		"ASSISTSEARCH_TYPE_PROMPT"},
	{ASSISTSEARCH_TYPE_UI,			"ASSISTSEARCH_TYPE_UI"},

		/* This must be the last entry! */
	{LITERAL_TABLE_END,		"UNKNOWN SEARCH TYPE"}
};

/*
 *  AssistIntervalTypeTable - used by GetLiteralString()
 */

static LITERAL_NAME_ENTRY AssistIntervalTypeTable [] =
{
	{ASSISTINTERVAL_TYPE_NONE,		"ASSISTINTERVAL_TYPE_NONE"},
	{ASSISTINTERVAL_TYPE_MINUTES,	"ASSISTINTERVAL_TYPE_MINUTES"},
	{ASSISTINTERVAL_TYPE_DAYS,		"ASSISTINTERVAL_TYPE_DAYS"},
	{ASSISTINTERVAL_TYPE_WEEK,		"ASSISTINTERVAL_TYPE_WEEK"},
	{ASSISTINTERVAL_TYPE_MONTH,		"ASSISTINTERVAL_TYPE_MONTH"},

		/* This must be the last entry! */
	{LITERAL_TABLE_END,		"UNKNOWN INTERVAL TYPE"}
};

	/* Hotspot Type Table */
#define NUM_HOTSPOT_TYPES 24

static char szHOTSPOTREC_TYPE_POPUP[]               = "POPUP";
static char szHOTSPOTREC_TYPE_HOTREGION[]           = "HOTREGION";
static char szHOTSPOTREC_TYPE_BUTTON[]              = "BUTTON";
static char szHOTSPOTREC_TYPE_FILE[]                = "FILE";
static char szHOTSPOTREC_TYPE_SECTION[]             = "SECTION";
static char szHOTSPOTREC_TYPE_ANY[]                 = "ANY";
static char szHOTSPOTREC_TYPE_HOTLINK[]             = "HOTLINK";
static char szHOTSPOTREC_TYPE_BUNDLE[]              = "BUNDLE";
static char szHOTSPOTREC_TYPE_V4_SECTION[]          = "V4 SECTION";
static char szHOTSPOTREC_TYPE_SUBFORM[]             = "SUBFORM";
static char szHOTSPOTREC_TYPE_ACTIVEOBJECT[]        = "ACTIVE OBJECT";
static char szHOTSPOTREC_TYPE_OLERICHTEXT[]         = "OLE RICH TEXT";
static char szHOTSPOTREC_TYPE_EMBEDDEDVIEW[]        = "EMBEDDED VIEW";
static char szHOTSPOTREC_TYPE_EMBEDDEDFPANE[]       = "EMBEDDED FOLDER PANE";
static char szHOTSPOTREC_TYPE_EMBEDDEDNAV[]         = "EMBEDDED NAVIGATOR";
static char szHOTSPOTREC_TYPE_FILEUPLOAD[]          = "FILE UPLOAD PLACEHOLDER";
static char szHOTSPOTREC_TYPE_MOUSEOVER[]		     = "MOUSE OVER TEXT POPUP";
static char szHOTSPOTREC_TYPE_EMBEDDEDOUTLINE[]     = "EMBEDDED OUTLINE";
static char szHOTSPOTREC_TYPE_EMBEDDEDCTL[]	     = "EMBEDDED CONTROL WINDOW";
static char szHOTSPOTREC_TYPE_EMBEDDEDCALENDARCTL[] = "EMBEDDED CALENDAR CONTROL";
static char szHOTSPOTREC_TYPE_EMBEDDEDSCHEDCTL[]    = "EMBEDDED SCHEDULE CONTROL";
static char szHOTSPOTREC_TYPE_RCLINK[]			     = "RESOURCE LINK";
static char szHOTSPOTREC_TYPE_EMBEDDEDEDITCTL[]     = "EMBEDDEDEDITCTL";
static char szHOTSPOTREC_TYPE_CONTACTLISTCTL[]      = "CONTACTLISTCTL";

static struct
{
	WORD    wHotSpotType;
	char   *szTypeStr;
}   HotSpotTypeTable[NUM_HOTSPOT_TYPES] =
{
	HOTSPOTREC_TYPE_POPUP,               szHOTSPOTREC_TYPE_POPUP,
	HOTSPOTREC_TYPE_HOTREGION,           szHOTSPOTREC_TYPE_HOTREGION,
	HOTSPOTREC_TYPE_BUTTON,              szHOTSPOTREC_TYPE_BUTTON,
	HOTSPOTREC_TYPE_FILE,                szHOTSPOTREC_TYPE_FILE,
	HOTSPOTREC_TYPE_SECTION,             szHOTSPOTREC_TYPE_SECTION,
	HOTSPOTREC_TYPE_ANY,                 szHOTSPOTREC_TYPE_ANY,
	HOTSPOTREC_TYPE_HOTLINK,             szHOTSPOTREC_TYPE_HOTLINK,
	HOTSPOTREC_TYPE_BUNDLE,              szHOTSPOTREC_TYPE_BUNDLE,
	HOTSPOTREC_TYPE_V4_SECTION,          szHOTSPOTREC_TYPE_V4_SECTION,
	HOTSPOTREC_TYPE_SUBFORM,             szHOTSPOTREC_TYPE_SUBFORM,
	HOTSPOTREC_TYPE_ACTIVEOBJECT,        szHOTSPOTREC_TYPE_ACTIVEOBJECT,
	HOTSPOTREC_TYPE_OLERICHTEXT,         szHOTSPOTREC_TYPE_OLERICHTEXT,
	HOTSPOTREC_TYPE_EMBEDDEDVIEW,        szHOTSPOTREC_TYPE_EMBEDDEDVIEW,
	HOTSPOTREC_TYPE_EMBEDDEDFPANE,       szHOTSPOTREC_TYPE_EMBEDDEDFPANE,
	HOTSPOTREC_TYPE_EMBEDDEDNAV,         szHOTSPOTREC_TYPE_EMBEDDEDNAV,
	HOTSPOTREC_TYPE_FILEUPLOAD,          szHOTSPOTREC_TYPE_FILEUPLOAD,
	HOTSPOTREC_TYPE_MOUSEOVER,		     szHOTSPOTREC_TYPE_MOUSEOVER,
	HOTSPOTREC_TYPE_EMBEDDEDOUTLINE,     szHOTSPOTREC_TYPE_EMBEDDEDOUTLINE,
	HOTSPOTREC_TYPE_EMBEDDEDCTL,	     szHOTSPOTREC_TYPE_EMBEDDEDCTL,
	HOTSPOTREC_TYPE_EMBEDDEDCALENDARCTL, szHOTSPOTREC_TYPE_EMBEDDEDCALENDARCTL,
	HOTSPOTREC_TYPE_EMBEDDEDSCHEDCTL,    szHOTSPOTREC_TYPE_EMBEDDEDSCHEDCTL,
	HOTSPOTREC_TYPE_RCLINK,			     szHOTSPOTREC_TYPE_RCLINK,
	HOTSPOTREC_TYPE_EMBEDDEDEDITCTL,     szHOTSPOTREC_TYPE_EMBEDDEDEDITCTL,
	HOTSPOTREC_TYPE_CONTACTLISTCTL,      szHOTSPOTREC_TYPE_CONTACTLISTCTL
};

ref class NSFAnalyzerEngine
{
private:
	HINSTANCE g_hDLL;	
	void init_ptrs(void);
	ListBox^ m_status_list;

	/* worker thread supported */	
	String^ m_logFilePath;
	String^ m_errlogFilePath;
	String^ m_outputFilePath;
	bool m_isHtml;
	NSFAnalyzer::ConfigurationTool^ m_cfg;
	System::ComponentModel::BackgroundWorker^ m_worker;
	int database_count;
	WORD m_note_class;
	String^ m_progScanDb; //ProgressScanDatabase;
	String^ m_progCurActivity; //ProgressCurrentActivity;
	String^ m_progMatch; //ProgressMatch;	
	void WriteStatus(String^);
	
public:
	NSFAnalyzerEngine(void);	
	bool BindPath();
	void GetServerList(vector<std::string>&);
	void GetDatabaseList(String^, vector<std::string>&);
	~NSFAnalyzerEngine();

	
	static const int PROGRESS_SCAN =-1;
	static const int PROGRESS_CURRENTACTIVITY = -2;
	static const int PROGRESS_MATCH = -3;

	/* worker thread supported */
	void BindStatusField(ListBox^);
	void BindConfiguration(NSFAnalyzer::ConfigurationTool^);
	void BindThreadWorker(System::ComponentModel::BackgroundWorker^);
	bool Search();
	bool ScanNSF();		
	void WriteLog(String^);
	void WriteLog(String^, bool);
	void WriteOutput(String^);
	void NotifyClient(String^, int);
	System::ComponentModel::BackgroundWorker^ GetWorkerThread(void);
	NSFScan::ScanIterator^ m_scanner;

	// public members the search callback func needs access to
	bool WorkThreadFired;

	property String^ ProgressScanDatabase {
		String^ get() { return m_progScanDb; }
		void set(String^ txt) { m_progScanDb = txt;	}
	}

	property String^ ProgressCurrentActivity {
		String^ get() { return m_progCurActivity; }
		void set(String^ txt) { m_progCurActivity = txt; }
	}

	property String^ ProgressMatch {
		String^ get() { return m_progMatch; }
		void set(String^ txt) {	m_progMatch = txt; }
	}

	property NSFScan::ScanIterator^ scanner {
		NSFScan::ScanIterator^ get() { return m_scanner; }
		void set(NSFScan::ScanIterator^ si) {	m_scanner = si; }
	}

	
	// public pointers to external functions
	static AUXGetServerNamesEx			pGetServerNamesEx;
	static AUXGetDatabaseNames			pGetDatabaseNames;
	static AUXOSLoadString				pOSLoadString;
	static AUXNSFDbOpen					pNSFDbOpen;
	static AUXNSFDbClose				pNSFDbClose;
	static AUXNSFSearch					pNSFSearch;
	static AUXNSFNoteOpen				pNSFNoteOpen;
	static AUXNSFDbGetNoteInfo			pNSFDbGetNoteInfo;
	static AUXNSFItemScan				pNSFItemScan;
	static AUXNSFNoteClose				pNSFNoteClose;
	static AUXNSFFormulaDecompile		pNSFFormulaDecompile; 
	static AUXOSLockObject				pOSLockObject;
	static AUXOSUnlockObject			pOSUnlockObject;
	static AUXOSMemFree					pOSMemFree;
	static AUXODSReadMemory				pODSReadMemory;
	static AUXListGetText				pListGetText;
	static AUXConvertTIMEDATEToText		pConvertTIMEDATEToText;
	static AUXODSLength					pODSLength;
	static AUXOSPathNetConstruct		pOSPathNetConstruct;
	static AUXNSFDbPathGet				pNSFDbPathGet;
	static AUXNSFItemGetText			pNSFItemGetText;
	static AUXOSCurrentTIMEDATE			pOSCurrentTIMEDATE;
	static AUXNSFNoteGetInfo			pNSFNoteGetInfo;
	static AUXNSFDbReplicaInfoGet		pNSFDbReplicaInfoGet;
	static AUXNSFDbInfoGet				pNSFDbInfoGet;
	static AUXNSFDbInfoParse			pNSFDbInfoParse;
	static AUXNSFGetSummaryValue		pNSFGetSummaryValue;
	static AUXNSFDbReadObject			pNSFDbReadObject;
	static AUXNSFDbFreeObject			pNSFDbFreeObject;
	static AUXNSFItemInfo				pNSFItemInfo;
	static AUXNSFNoteExtractWithCallback pNSFNoteExtractWithCallback;
	static AUXNSFItemInfoNext			pNSFItemInfoNext;
	static AUXThreadInitialize			pThreadInitialize;
	static AUXThreadTerminate			pThreadTerminate;

};
