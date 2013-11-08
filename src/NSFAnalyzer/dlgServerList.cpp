#include "StdAfx.h"
#include "dlgServerList.h"

using namespace NSFAnalyzer;

void dlgServerList::setServers(vector<std::string>& serverVector) {
	this->cbxServerList->Items->Clear();	
	vector<string>::const_iterator cii;	
	String ^server;
	std::string cppServer;
	
	for(cii=serverVector.begin(); cii!=serverVector.end(); cii++) {
		cppServer = *cii;
		server = gcnew String(cppServer.c_str());
		this->cbxServerList->Items->Add(server);
	}
}