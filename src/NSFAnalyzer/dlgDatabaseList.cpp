#include "StdAfx.h"
#include "dlgDatabaseList.h"

using namespace NSFAnalyzer;
using namespace Microsoft::Win32;
using namespace System::Runtime::InteropServices;
using namespace Microsoft::Win32;
using namespace Windows::Forms;

void dlgDatabaseList::setDatabases(vector<std::string>& dbVector) {	
	this->tvDbList->Nodes->Clear();
	this->FillTree(dbVector);
}

void dlgDatabaseList::FillTree(vector<std::string>& dbVector) {
	String ^db;
	std::string cppDb;
	vector<string>::const_iterator cii;	
	TreeNodeCollection^ nodes; 

	for(cii=dbVector.begin(); cii!=dbVector.end(); cii++) {
		nodes = this->tvDbList->Nodes;
		cppDb = *cii;
		db = (gcnew String(cppDb.c_str()))->Replace('\\', '/');
		if (!this->dir_table->ContainsKey(db)) {
			cli::array<String^>^p=db->Split('/');
			for (int i=0; i<p->Length; i++) {	
				if (nodes->ContainsKey(p[i])) {
					nodes = nodes[p[i]]->Nodes;
				} else {
					nodes = nodes->Add(p[i], p[i])->Nodes;
				}			
			}
		}
	}
}
