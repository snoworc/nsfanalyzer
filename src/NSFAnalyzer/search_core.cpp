#include "stdafx.h"
#include "search_core.h"

using namespace NSFAnalyzer;
using namespace System::Runtime::InteropServices;
using namespace Microsoft::Win32;
using namespace Windows::Forms;

NSFAnalyzerEngine::NSFAnalyzerEngine(void) {	
	this->WorkThreadFired = false;
	int pos = Application::ExecutablePath->LastIndexOf("\\");
	String^ exePath = Application::ExecutablePath->Substring(0, pos);
	m_logFilePath = exePath + "\\scan_log.txt";
	m_errlogFilePath = exePath + "\\error_log.txt";	
	init_ptrs();
}

NSFAnalyzerEngine::~NSFAnalyzerEngine() {		
	if (this->WorkThreadFired) {
		//this->pThreadTerminate(); no, only one term is needed per c++ api help, which should apply to multithreading here as well. I think this line causes failure during subsequent app launches IF notes client is already launched.
	}
	FreeLibrary(g_hDLL);
}

void NSFAnalyzerEngine::init_ptrs(void) {	
	try {		
		if (!this->BindPath()){
			MessageBox::Show("Unable to bind run-time path for Analyze_CAPI.dll", "Fatal Error", MessageBoxButtons::OK, MessageBoxIcon::Error);	
			return;
		}
		g_hDLL= LoadLibrary("Analyze_CAPI.dll");	
		if (!g_hDLL) {
			MessageBox::Show("Unable to load Analyze_CAPI.dll functions", "Fatal Error", MessageBoxButtons::OK, MessageBoxIcon::Error);	
			return;
		}

		pGetServerNamesEx		= (AUXGetServerNamesEx)GetProcAddress(g_hDLL, "GetServerNamesEx");
		pGetDatabaseNames		= (AUXGetDatabaseNames)GetProcAddress(g_hDLL, "GetDatabaseNames");
		pOSLoadString			= (AUXOSLoadString)GetProcAddress(g_hDLL, "ATOM_OSLoadString");
		pNSFDbOpen				= (AUXNSFDbOpen)GetProcAddress(g_hDLL, "ATOM_NSFDbOpen");
		pNSFDbClose				= (AUXNSFDbClose)GetProcAddress(g_hDLL, "ATOM_NSFDbClose");
		pNSFSearch				= (AUXNSFSearch)GetProcAddress(g_hDLL, "ATOM_NSFSearch");
		pNSFNoteOpen			= (AUXNSFNoteOpen)GetProcAddress(g_hDLL, "ATOM_NSFNoteOpen");
		pNSFDbGetNoteInfo		= (AUXNSFDbGetNoteInfo)GetProcAddress(g_hDLL, "ATOM_NSFDbGetNoteInfo");
		pNSFItemScan			= (AUXNSFItemScan)GetProcAddress(g_hDLL, "ATOM_NSFItemScan");
		pNSFNoteClose			= (AUXNSFNoteClose)GetProcAddress(g_hDLL, "ATOM_NSFNoteClose");
		pNSFFormulaDecompile	= (AUXNSFFormulaDecompile)GetProcAddress(g_hDLL, "ATOM_NSFFormulaDecompile");
		pOSLockObject			= (AUXOSLockObject)GetProcAddress(g_hDLL, "ATOM_OSLockObject");
		pOSUnlockObject			= (AUXOSUnlockObject)GetProcAddress(g_hDLL, "ATOM_OSUnlockObject");
		pOSMemFree				= (AUXOSMemFree)GetProcAddress(g_hDLL, "ATOM_OSMemFree");
		pODSReadMemory			= (AUXODSReadMemory)GetProcAddress(g_hDLL, "ATOM_ODSReadMemory");
		pListGetText			= (AUXListGetText)GetProcAddress(g_hDLL, "ATOM_ListGetText");
		pConvertTIMEDATEToText	= (AUXConvertTIMEDATEToText)GetProcAddress(g_hDLL, "ATOM_ConvertTIMEDATEToText");
		pODSLength				= (AUXODSLength)GetProcAddress(g_hDLL, "ATOM_ODSLength");
		pOSPathNetConstruct		= (AUXOSPathNetConstruct)GetProcAddress(g_hDLL, "ATOM_OSPathNetConstruct");
		pNSFDbPathGet			= (AUXNSFDbPathGet)GetProcAddress(g_hDLL, "ATOM_NSFDbPathGet");
		pNSFItemGetText			= (AUXNSFItemGetText)GetProcAddress(g_hDLL, "ATOM_NSFItemGetText");
		pOSCurrentTIMEDATE		= (AUXOSCurrentTIMEDATE)GetProcAddress(g_hDLL, "ATOM_OSCurrentTIMEDATE");
		pNSFNoteGetInfo			= (AUXNSFNoteGetInfo)GetProcAddress(g_hDLL, "ATOM_NSFNoteGetInfo");
		pNSFDbReplicaInfoGet	= (AUXNSFDbReplicaInfoGet)GetProcAddress(g_hDLL, "ATOM_NSFDbReplicaInfoGet");	
		pNSFDbInfoGet			= (AUXNSFDbInfoGet)GetProcAddress(g_hDLL, "ATOM_NSFDbInfoGet");
		pNSFDbInfoParse			= (AUXNSFDbInfoParse)GetProcAddress(g_hDLL, "ATOM_NSFDbInfoParse");
		pNSFGetSummaryValue		= (AUXNSFGetSummaryValue)GetProcAddress(g_hDLL, "ATOM_NSFGetSummaryValue");
		pNSFDbReadObject		= (AUXNSFDbReadObject)GetProcAddress(g_hDLL, "ATOM_NSFDbReadObject");
		pNSFDbFreeObject		= (AUXNSFDbFreeObject)GetProcAddress(g_hDLL, "ATOM_NSFDbFreeObject");
		pNSFItemInfo			= (AUXNSFItemInfo)GetProcAddress(g_hDLL, "ATOM_NSFItemInfo");
		pNSFNoteExtractWithCallback	= (AUXNSFNoteExtractWithCallback)GetProcAddress(g_hDLL, "ATOM_NSFNoteExtractWithCallback");
		pNSFItemInfoNext		= (AUXNSFItemInfoNext)GetProcAddress(g_hDLL, "ATOM_NSFItemInfoNext");
		pThreadInitialize		= (AUXThreadInitialize)GetProcAddress(g_hDLL, "ThreadInitialize");			
		pThreadTerminate		= (AUXThreadTerminate)GetProcAddress(g_hDLL, "ThreadTerminate");			
	} catch(Exception^ ex) {
		MessageBox::Show(ex->Message + "\n" + ex->StackTrace, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
void NSFAnalyzerEngine::WriteStatus(String^ txt) {
	if (NSFAnalyzerEngine::m_status_list) {
		NSFAnalyzerEngine::m_status_list->Items->Insert(0, txt);
	}
}

void NSFAnalyzerEngine::WriteLog(String^ txt) {
	this->WriteLog(txt, false);
}

void NSFAnalyzerEngine::WriteLog(String^ txt, bool isError) {	
	File::AppendAllText(((isError) ? this->m_errlogFilePath : this->m_logFilePath), txt + "\n");
}

void NSFAnalyzerEngine::WriteOutput(String^ txt) {	
	File::AppendAllText(m_outputFilePath, txt);
}

bool NSFAnalyzerEngine::BindPath() {
	RegistryKey^ clsroot;
	RegistryKey^ subkey;
	RegistryKey^ subsubkey;
	String^ dll_path;

	try {
		clsroot = Registry::ClassesRoot;
	
		if (!clsroot) {
			MessageBox::Show("Unable to access system registry: class root", "Fatal Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return false;
		}
	
		subkey = clsroot->OpenSubKey(".nsf");
		if (!subkey) {
			MessageBox::Show("Class root key \".nsf\" not found in registry.", "Fatal Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return false;
		}
		subsubkey = subkey->OpenSubKey("Shell\\Open\\Command");
		if (!subsubkey) {
			MessageBox::Show("Class root key \".nsf\\Shell\\Open\\Command\" not found in registry.", "Fatal Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return false;
		}
		dll_path = safe_cast<String ^>(subsubkey->GetValue("")); // pull the default
		if (dll_path->Length > 0) {
			dll_path = dll_path->Substring(0, (dll_path->IndexOf(L"notes.exe")) - 1);			
		}
		
		String^ path = System::Environment::GetEnvironmentVariable(L"PATH");
		if (!path->Contains(dll_path)) {
			Environment::SetEnvironmentVariable(L"PATH", path + ";" + dll_path);			
			this->WriteLog("Added \"" + dll_path + "\" temporarily to your PATH environment variable.");
		}

		return true;

	} catch(Exception^ ex) {
		MessageBox::Show(ex->Message + "\n" + ex->StackTrace, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return false;

	} finally {
		if (clsroot) clsroot->Close();
		if (subkey) subkey->Close();
		if (subsubkey) subsubkey->Close();
	}			
}

void NSFAnalyzerEngine::GetServerList(vector<std::string>& serverNames) {		
	char cppServers[MAX_SERVERS][MAXPATH];
	if (!pGetServerNamesEx) {
		MessageBox::Show("Invalid handle to function pointer: pGetServerNamesEx", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	try {
		std::string stdServer;
		WORD numServers = (WORD)this->pGetServerNamesEx(cppServers);
		if (numServers == 0) {
			stdServer = "Local";
			serverNames.push_back(stdServer);
			MessageBox::Show("No servers found. Check connection.", "Error - No Servers", Windows::Forms::MessageBoxButtons::OK, Windows::Forms::MessageBoxIcon::Stop);
		} else {
			for (int i=0; i<numServers; i++) {
				stdServer = cppServers[i];
				serverNames.push_back(stdServer);
			}
		}
	} catch(Exception^ ex) {
		MessageBox::Show(ex->Message + "\n" + ex->StackTrace, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

void NSFAnalyzerEngine::GetDatabaseList(String^ serverName, vector<std::string>& databaseNames) {			
	char* cppServer = (char*)Marshal:: StringToHGlobalAnsi(serverName).ToPointer();		
	char cppDatabases[MAX_ENTRIES][MAXPATH];		
	try {
		std::string stdDatabase;
		this->database_count = (int)(WORD)this->pGetDatabaseNames(NULL, cppServer, cppDatabases);		
		if (this->database_count == 0) {
			MessageBox::Show("No databases found. Check connection.", "Error - No Servers", Windows::Forms::MessageBoxButtons::OK, Windows::Forms::MessageBoxIcon::Stop);
		} else {
			for (int i=0; i<this->database_count; i++) {
				stdDatabase = cppDatabases[i];
				databaseNames.push_back(stdDatabase);				
			}			
		}
	} catch(Exception^ ex) {
		MessageBox::Show(ex->Message + "\n" + ex->StackTrace, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	} finally {
		Marshal::FreeHGlobal((IntPtr)cppServer);
		this->WriteLog("Database list retrieved: " + this->database_count);
	}
}

void NSFAnalyzerEngine::BindStatusField(ListBox^ lbx) {
	this->m_status_list = lbx;
}
void NSFAnalyzerEngine::BindConfiguration(NSFAnalyzer::ConfigurationTool^ cfg) {
	this->m_cfg = cfg;
}

void NSFAnalyzerEngine::BindThreadWorker(System::ComponentModel::BackgroundWorker^ worker) {
	m_worker = worker;
}

bool NSFAnalyzerEngine::Search() {
	ListBox^ lbx;
	System::Collections::IDictionaryEnumerator^ e;
	NSFScan::ScanResult^ scan_result;
	this->database_count = 0;
	this->scanner = gcnew NSFScan::ScanIterator();	
	this->scanner->note_class_table = gcnew NoteClassTable();		 
	bool status = false;
	STATUS Error;	
	int numDbs = 0;
	String^	output = String::Empty;
	String^ styleTag = "<style type=\"text/css\">th,td {font-size:10pt; padding:3px;}</style>";

	this->m_isHtml = m_cfg->GetFileFormat()->ToLower()->Equals("html");
	this->m_outputFilePath = m_cfg->GetFilePath();
	File::Delete(m_outputFilePath);

	void* ptr = GCHandle::ToIntPtr(GCHandle::Alloc(this->scanner)).ToPointer();
	
	m_note_class = ((m_cfg->GetIsDesignOnly()) ? NOTE_CLASS_ALLNONDATA : NOTE_CLASS_ALL);

	this->scanner->ExactMatchesOnly = this->m_cfg->GetIsExactMatch();

	DBHANDLE    dir_handle;          /* handle for directory */
	char *cppServer = (char*)Marshal::StringToHGlobalAnsi(m_cfg->GetServer()->Equals("Local") ? "" : m_cfg->GetServer()).ToPointer();
	try {
		if (m_cfg->GetDatabase()->Length == 0) {
			// multi-db scan
			this->NotifyClient("Scanning server: " + m_cfg->GetServer(), NSFAnalyzerEngine::PROGRESS_CURRENTACTIVITY);					
			output = String::Empty;
			if (this->m_isHtml) {
				output = "<html>\n<head><title>Search Results</title>" + styleTag + "</head>\n<body style=\"font-family:sans-serif\"><form>\n\n";
				output += "<h1>Search results</h1><h3>Server: " + m_cfg->GetServer() + "</h3>";
				output += "<h4>Search Database:</strong>-- All --</h4>";
				output += "<strong>Search Tokens:</strong> ";
				for (int n = 0; n< m_cfg->GetSearchKeys()->Items->Count; n++) {
					output += m_cfg->GetSearchKeys()->Items[n] + ", ";
				}
				output = output->Substring(0, output->Length - 2) + "<br /><br />";
				output += "<table border=\"1\" cellpadding=\"0\" cellspacing=\"0\"><tr><th>Database Title</th><th>Database Path</th><th>Design Class</th><th>Design Name</th><th>Field Name</th><th>Data Type</th><th>Details</th><th>Match Token</th><th>Match Type</th></tr>\n";			
			} else {
				output = "Server,Database Title,Database Path,Design Class,Design Name,Field Name,Data Type,Details,Match Token,Match Type\n";			
			}
			this->WriteOutput(output);
			output = String::Empty;

			char full_netpath[MAXPATH] = "";
			if (Error = NSFAnalyzerEngine::pOSPathNetConstruct(NULL, cppServer, "", full_netpath))
				return 0;
			if (Error = NSFAnalyzerEngine::pNSFDbOpen (full_netpath, &dir_handle))
				return 0;

			/* begin flag override:
				set flags for building a db collection, these flags are re-used when doing the scan */
			this->scanner->IsMatch = (this->m_cfg->GetIncludeFlag() == false && this->m_cfg->GetExcludeFlag() == false);
			
			if (this->m_cfg->GetExcludeFlag()) {
				lbx = this->m_cfg->GetExcludeFolders();
			} else if(this->m_cfg->GetIncludeFlag()) {
				lbx = this->m_cfg->GetIncludeFolders();
			}
			if (lbx) for (int i=0; i<lbx->Items->Count; i++) {
				this->scanner->Search_Tokens->Add(safe_cast<System::String^>(lbx->Items[i]));
			}
			
			/* end of flag override */

			if (Error = pNSFSearch(dir_handle,		  // directory handle
								   NULLHANDLE,        // selection formula
								   NULL,              // title of view in formula
								   SEARCH_FILETYPE +  // search for files
								   SEARCH_SUMMARY,    // return a summary buffer
								   FILE_DBANY +       // find any .NS? file
								   FILE_RECURSE +     // find subdirectories
								   FILE_NOUPDIRS,     // don't find the ".." dir					
								   NULL,              // starting date
								   BuildDbList,       // call for each file found
								   ptr,               // argument to action routine
								   NULL)) {           // returned ending date (unused)
				if (Error != THREAD_CANCEL) {
					MessageBox::Show("Error Code: " + Error + " Reason: " + ERR(Error) + ". Error encountered searching for databases on server.", "Error in pNSFSearch", MessageBoxButtons::OK, MessageBoxIcon::Error);			
					return false;
				}
			}
			/* reset flags, search tokens are modified here. the IsMatch flag will be modified inside the inner scanNSF function */
			this->scanner->Search_Tokens = gcnew System::Collections::Generic::List<String^>(10);
			lbx = this->m_cfg->GetSearchKeys();
			for (int i=0; i<lbx->Items->Count; i++) {
				this->scanner->Search_Tokens->Add(safe_cast<System::String^>(lbx->Items[i]));
			}
		
			this->database_count = scanner->Search_Databases->Count;
			for (int i=0; i<this->database_count; i++) {
				this->scanner->CurrentDatabase = this->scanner->Search_Databases[i];
				if (this->m_worker->CancellationPending == true) {
					return false;
				}
				this->scanner->ScanTotal++;
				this->scanner->SearchQuery->DatabaseFile = this->scanner->CurrentDatabase;
				this->ScanNSF();
				
				e = this->scanner->SearchResults->GetEnumerator();
				while (e->MoveNext()) {
					scan_result = safe_cast<NSFScan::ScanResult^>(e->Value);
					if (this->m_isHtml) {
						output += "<tr><td>" + this->scanner->CurrentDatabaseTitle + "</td><td>" + 
								  this->scanner->CurrentDatabase + "</td><td>" + 
								  scan_result->DesignClass + "</td><td>" + 
								  scan_result->DesignTitle + "</td><td>" + 
								  scan_result->FieldName  + "</td><td>" + 
								  scan_result->DataType + "</td><td>" + 
								  scan_result->GetDesignDetails() + "</td><td>" + 
								  scan_result->MatchToken + "</td><td>" + 
								  ((scan_result->MatchType == EXACT_MATCH) ? "Exact Match" : "Possible Match") + "</td></tr>\n";
					} else {
						output += m_cfg->GetServer() + "," + 
								  this->scanner->CurrentDatabaseTitle + "," + 
								  this->scanner->CurrentDatabase + "," + 
								  scan_result->DesignClass + "," + 
								  scan_result->DesignTitle + "," + 
								  scan_result->FieldName + "," + 
								  scan_result->DataType + "," + 							  
								  scan_result->GetDesignDetails(false) + "," + 
								  scan_result->MatchToken + "," + 
								  ((scan_result->MatchType == EXACT_MATCH) ? "Exact Match" : "Possible Match") + "\n";
					}
					this->WriteOutput(output);
					output = String::Empty;
				}
				this->scanner->SearchResults = gcnew System::Collections::Hashtable(200);			
			}	
			if (this->scanner->MatchCount == 0) {
				MessageBox::Show("No results found", "No Results", MessageBoxButtons::OK, MessageBoxIcon::Information);
				File::Delete(this->m_outputFilePath);
			} else {
				if (this->m_isHtml) {
					output = "</table><br />";
					output += "<strong>Total matches found:</strong> " + this->scanner->MatchCount + "<br />";
					output += "<strong>Total items scanned:</strong> " + this->scanner->ScanCount + "<br />";
					output += "<strong>Total databases scanned:</strong> " + this->scanner->ScanTotal;
					output += "</form></body></html>";
					this->WriteOutput(output);
					output = String::Empty;
				}

				if (this->m_cfg->IsAutoLaunching) {
					try {
						System::Diagnostics::Process::Start(m_outputFilePath);
					 } catch(System::Exception^ ex) {
						 MessageBox::Show(ex->Message + "\n\n" + ex->StackTrace, "Unable to open output file: " + m_outputFilePath, MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
						 return status;
					 }
				}
			}		
		} else {	
			// single db scan
			lbx = this->m_cfg->GetSearchKeys();
			for (int i=0; i<lbx->Items->Count; i++) {
				this->scanner->Search_Tokens->Add(safe_cast<System::String^>(lbx->Items[i]));
			}
			this->NotifyClient("Scanning database: " + m_cfg->GetServer() + "!!" + m_cfg->GetDatabase(), NSFAnalyzerEngine::PROGRESS_CURRENTACTIVITY);		
			this->scanner->ScanTotal = 1;
			this->database_count = 1;
			this->scanner->CurrentDatabase = m_cfg->GetDatabase();
			this->scanner->SearchQuery->DatabaseFile = this->scanner->CurrentDatabase;
			status = this->ScanNSF();

			if (this->scanner->MatchCount == 0) {
				MessageBox::Show("No results found", "No Results", MessageBoxButtons::OK, MessageBoxIcon::Information);			
			} else {
				if (this->scanner->SearchResults->Count > 0) {
					e = this->scanner->SearchResults->GetEnumerator();
					if (this->m_isHtml) {
						output += "<html>\n<head><title>Search Results</title>" + styleTag + "</head>\n<body style=\"font-family:sans-serif\"><form>\n\n";
						output += "<h1>Search results</h1><h3>Server: " + m_cfg->GetServer() + "</h3>";
						output += "<h4>Search Database:</strong> " + m_cfg->GetDatabase() + "</h4>";
						output += "<strong>Search Tokens:</strong> ";
						for (int n = 0; n< m_cfg->GetSearchKeys()->Items->Count; n++) {
							output += m_cfg->GetSearchKeys()->Items[n] + ", ";
						}
						output = output->Substring(0, output->Length - 2) + "<br /><br />";
						output += "<table border=\"1\" cellspacing=\"0\" cellpadding=\"0\"><tr><th>Database Title</th><th>Database Path</th><th>Design Class</th><th>Design Name</th><th>Field Name</th><th>Data Type</th><th>Design Details</th><th>Match Token</th><th>Match Type</th></tr>\n";			

						while (e->MoveNext()) {
							scan_result = safe_cast<NSFScan::ScanResult^>(e->Value);
							output += "<tr><td>" + this->scanner->CurrentDatabaseTitle + "</td><td>" + 
									  this->scanner->CurrentDatabase + "</td><td>" + 
									  scan_result->DesignClass + "</td><td>" + 
									  scan_result->DesignTitle + "</td><td>" + 
									  scan_result->FieldName  + "</td><td>" + 
									  scan_result->DataType + "</td><td>" + 
									  scan_result->GetDesignDetails() + "</td><td>" + 
									  scan_result->MatchToken + "</td><td>" + 
									  ((scan_result->MatchType == EXACT_MATCH) ? "Exact Match" : "Possible Match") + "</td></tr>\n";
						}
						output += "</table><br />";
						output += "<strong>Total matches found:</strong> " + this->scanner->MatchCount + "<br />";
						output += "<strong>Total items scanned:</strong> " + this->scanner->ScanCount + "<br />";
						output += "<strong>Total databases scanned:</strong> " + this->scanner->ScanTotal;
						output += "</form></body></html>";						
						
					} else {
						output += "Server,Database Title,Database Path,Design Class,Design Name,Field Name,Data Type,Design Details,Match Token,Match Type\n";
						while (e->MoveNext()) {
							scan_result = safe_cast<NSFScan::ScanResult^>(e->Value);
							output += m_cfg->GetServer() + "," + 
									  this->scanner->CurrentDatabaseTitle + "," + 
									  this->scanner->CurrentDatabase + "," + 
									  scan_result->DesignClass + "," + 
									  scan_result->DesignTitle + "," + 
									  scan_result->FieldName + "," + 
									  scan_result->DataType + "," + 
									  scan_result->GetDesignDetails(false) + "," + 
									  scan_result->MatchToken + "," + 
									  ((scan_result->MatchType == EXACT_MATCH) ? "Exact Match" : "Possible Match") + "\n";
						}
					}
					this->WriteOutput(output);
				
					if (this->m_cfg->IsAutoLaunching) {
						try {
							System::Diagnostics::Process::Start(m_outputFilePath);
						 } catch(System::Exception^ ex) {
							 MessageBox::Show(ex->Message + "\n\n" + ex->StackTrace, "Unable to open output file: " + m_outputFilePath, MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
							 return status;
						 }
					}
				}
			}
		}

		this->NotifyClient("Total matches found: " + this->scanner->MatchCount, NSFAnalyzerEngine::PROGRESS_MATCH);
		Threading::Thread::Sleep(200);
		this->NotifyClient("Total items scanned: " + this->scanner->ScanCount, NSFAnalyzerEngine::PROGRESS_MATCH);
		Threading::Thread::Sleep(200);
		this->NotifyClient("Total databases scanned: " + this->scanner->ScanTotal, NSFAnalyzerEngine::PROGRESS_MATCH);		
		Threading::Thread::Sleep(200);
	} finally {
		Marshal::FreeHGlobal((IntPtr)cppServer);
	}
	return status;
}


bool NSFAnalyzerEngine::ScanNSF() {
	STATUS				Error;	
	DHANDLE				hDB;	
	TIMEDATE			tdSearchSince;
	char* cppServer		= (char*)Marshal::StringToHGlobalAnsi(m_cfg->GetServer()).ToPointer();
	char* cppDatabase	= (char*)Marshal::StringToHGlobalAnsi(this->scanner->CurrentDatabase).ToPointer();
	char retDbPath[MAXPATH] = "";
	char db_info[NSF_INFO_SIZE];
	char dbTitle[MAXPATH] = "";
	
	tdSearchSince.Innards[1] = ANYDAY;
	tdSearchSince.Innards[0] = ALLDAY;

	try {
		if (Error = this->pOSPathNetConstruct(NULL, (strcmp(cppServer, "Local") == -1) ? cppServer : "", cppDatabase, retDbPath)) {
			MessageBox::Show("Error Code: " + Error + " Reason: " + ERR(Error) + ".", "Error in pOSPathNetConstruct", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return false;
		}
		
		if (Error =this->pNSFDbOpen(retDbPath, &hDB )) {
			if (ERR(Error) == 582) {
				this->NotifyClient("Skipping: " + this->scanner->CurrentDatabase + ". Unable to scan. Check your ACL access", NSFAnalyzerEngine::PROGRESS_MATCH);
				this->WriteLog("Skipping: " + this->scanner->CurrentDatabase + ". Unable to scan. Check your ACL access");
			} else {
				MessageBox::Show("Error Code: " + Error + " Reason: " + ERR(Error) + ". Unable to open database", "Error in pNSFDbOpen", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			return false;
		}
			
		if (false == this->pNSFDbInfoGet(hDB, db_info)) {
			this->pNSFDbInfoParse(db_info, INFOPARSE_TITLE, dbTitle, NSF_INFO_SIZE);			
			this->scanner->CurrentDatabaseTitle = gcnew String(dbTitle);
		}		
		this->scanner->IsMatch = false;
		this->scanner->hdb = hDB;
						
		this->NotifyClient("Scanning: " + this->scanner->CurrentDatabase + " - database " + this->scanner->ScanTotal + " out of " + this->database_count, NSFAnalyzerEngine::PROGRESS_SCAN);
		this->WriteLog("Scanning: " + this->scanner->CurrentDatabase + " - database " + this->scanner->ScanTotal + " out of " + this->database_count);

		void* ptr = GCHandle::ToIntPtr(GCHandle::Alloc(this)).ToPointer();
		if (Error = pNSFSearch(hDB, NULLHANDLE, NULL, SEARCH_SUMMARY, m_note_class, &tdSearchSince, ScanNote, ptr, NULL )) {
			if (Error != THREAD_CANCEL) {
				MessageBox::Show("Error Code: " + Error + " Reason: " + ERR(Error) + ". Error encountered searching for design notes.", "Error in pNSFSearch", MessageBoxButtons::OK, MessageBoxIcon::Error);			
				return false;
			}
			return true;
		}				

		return true;

	} catch(Exception^ ex) {
		MessageBox::Show(ex->Message + "\n" + ex->StackTrace, "Error in pNSFSearch", MessageBoxButtons::OK, MessageBoxIcon::Error);			
		
		return false;

	} finally {
		if (hDB == NOERROR) {
			pNSFDbClose(hDB);
		}
		Marshal::FreeHGlobal((IntPtr)cppServer);
		Marshal::FreeHGlobal((IntPtr)cppDatabase);
	}
	
}


void NSFAnalyzerEngine::NotifyClient(String^ msg, int progress) {
	if (progress >= 0) {
		this->m_worker->ReportProgress(progress);
		Threading::Thread::Sleep(100);
	} else {
		switch (progress) {
			case NSFAnalyzerEngine::PROGRESS_SCAN: 
				this->ProgressScanDatabase = msg;
				break;
			case NSFAnalyzerEngine::PROGRESS_CURRENTACTIVITY:
				this->ProgressCurrentActivity = msg;
				break;
			case NSFAnalyzerEngine::PROGRESS_MATCH:
				this->ProgressMatch = msg;
				break;	
		}
		this->m_worker->ReportProgress(1);		
	}
	
}


System::ComponentModel::BackgroundWorker^ NSFAnalyzerEngine::GetWorkerThread(){ 
	return m_worker; 
}