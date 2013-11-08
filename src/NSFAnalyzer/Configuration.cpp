#include "StdAfx.h"
#include "Configuration.h"

using namespace NSFAnalyzer;

ConfigurationTool::ConfigurationTool() {}

bool ConfigurationTool::Read(String^ file) {
/*
Example xml file:

<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<NSFAnalyze>
	<OutputFormat>csv</OutputFormat>
	<OutputFile>C:\tbnscanner_design.csv</OutputFile>
	<Server>CN=FTWWDLDAD001/O=RRD/C=US</Server>
	<Database>bnsf\dwu.nsf</Database>
	<Include>
		<Enabled>yes</Enabled>
		<Recurse>no</Recurse>
		<FolderList>
			<Folder>website</Folder>
			<Folder>stuff</Folder>
		</FolderList>
	</Include>
	<Exclude>
		<Enabled>no</Enabled>
	</Exclude>
	<KeywordList>
		<Keyword>searchtoken1</Keyword>
		<Keyword>searchtoken2</Keyword>
	</KeywordList>
	<AnalyzeData>no</AnalyzeData>
	<ExactMatch>yes</ExactMatch>
	<AutoLaunch>yes</AutoLaunch>	
</NSFAnalyze>
*/	
	XmlNode^ node;
	FileStream^ fs;
	try {
		fs = File::OpenRead(file);
	} catch (System::IO::FileNotFoundException^) {
		/* it is ok, the end user has not saved a file yet... */		
		return true;
	}
	XmlReader^ xrd = XmlReader::Create(fs);
	ListBox^ lbx;

	// build the in-memory representation
	XmlDocument^ xd = gcnew XmlDocument;
	xd->Load(xrd);

	node = xd->GetElementsByTagName("OutputFormat")->Item(0);
	this->SetFileFormat(node->InnerText->ToLower());

	node = xd->GetElementsByTagName("OutputFile")->Item(0);
	this->SetFilePath(node->InnerText);
	
	node = xd->GetElementsByTagName("Server")->Item(0);
	this->SetServer(node->InnerText);

	node = xd->GetElementsByTagName("Database")->Item(0);
	this->SetDatabase(node->InnerText);

	node = xd->GetElementsByTagName("Include")[0];
	if (node) {
		try {
			this->SetIncludeFlag(node->ChildNodes->Item(0)->InnerText->Equals("yes"));
		} catch (Exception^) {
			this->SetIncludeFlag(false);
		}
		try {
			if (node->ChildNodes->Count > 1) {
				this->SetIncludeRecurseFlag(node->ChildNodes->Item(1)->InnerText->Equals("yes"));
			} else {
				this->SetIncludeRecurseFlag(false);
			}			
		} catch (Exception^) {
			this->SetIncludeRecurseFlag(false);
		}
		try {			
			if (node->ChildNodes->Count > 2) {
				lbx = gcnew ListBox();
				for (int i=0; i<node->ChildNodes->Item(2)->ChildNodes->Count; i++) {
					lbx->Items->Add(node->ChildNodes->Item(2)->ChildNodes->Item(i)->InnerText);
				}
				this->SetIncludeFolders(lbx);
			}			
		} catch(Exception^) {
			/* do not store lbx */
		}
	} else {
		this->SetIncludeFlag(false);
		this->SetIncludeRecurseFlag(false);
	}

	node = xd->GetElementsByTagName("Exclude")[0];
	if (node) {
		try {
			this->SetExcludeFlag(node->ChildNodes->Item(0)->InnerText->Equals("yes"));
		} catch (Exception^) {
			this->SetExcludeFlag(false);
		}
		try {
			if (node->ChildNodes->Count > 1) {
				this->SetExcludeRecurseFlag(node->ChildNodes->Item(1)->InnerText->Equals("yes"));
			} else {
				this->SetExcludeRecurseFlag(false);
			}
		} catch (Exception^) {
			this->SetExcludeRecurseFlag(false);
		}
		try {
			if (node->ChildNodes->Count > 2) {
				lbx = gcnew ListBox();
				for (int i=0; i<node->ChildNodes->Item(2)->ChildNodes->Count; i++) {
					lbx->Items->Add(node->ChildNodes->Item(2)->ChildNodes->Item(i)->InnerText);
				}
				this->SetExcludeFolders(lbx);
			}			
		} catch(Exception^) {
			/* do not store lbx */
			
		}
	} else {
		this->SetExcludeFlag(false);
		this->SetExcludeRecurseFlag(false);
	}
	
	node = xd->GetElementsByTagName("KeywordList")[0];
	if (node) {
		lbx = gcnew ListBox();
			for (int i=0; i<node->ChildNodes->Count; i++) {
				lbx->Items->Add(node->ChildNodes->Item(i)->InnerText);
			}
		this->SetSearchKeys(lbx);
	}
	
	try {
		node = xd->GetElementsByTagName("AutoLaunch")->Item(0);
		this->IsAutoLaunching = node->InnerText->Equals("yes");
	} catch (Exception^) {
	}

	xrd->Close();
	fs->Close();
	
	return false;	 
}

void ConfigurationTool::Write(String^ file){
	XmlDocument^ xd = gcnew XmlDocument;		
	XmlElement^ innards;
	XmlDeclaration^ decl = xd->CreateXmlDeclaration("1.0", "UTF-8", "yes");
	xd->AppendChild(decl);
			 
	XmlElement^ root = xd->CreateElement("NSFAnalyze");
	XmlElement^ child = xd->CreateElement("OutputFormat");
			 
	child->InnerText = this->GetFileFormat();
	root->AppendChild(child);

	child = xd->CreateElement("OutputFile");
	child->InnerText = this->GetFilePath();
	root->AppendChild(child);

	child = xd->CreateElement("Server");
	child->InnerText = this->GetServer();
	root->AppendChild(child);

	child = xd->CreateElement("Database");
	child->InnerText = this->GetDatabase();
	root->AppendChild(child);

	child = xd->CreateElement("Include");
	innards = xd->CreateElement("Enabled");
	if (this->GetIncludeFlag()) {				 				 				 				 
		innards->InnerText = "yes";
		child->AppendChild(innards);
		innards = xd->CreateElement("Recurse");				  
		innards->InnerText = ((this->GetIncludeRecurseFlag()) ? "yes" : "no");
				 child->AppendChild(innards);
				 innards = xd->CreateElement("FolderList");				 
				 if (this->GetIncludeFolders()->Items->Count > 0) {
					 XmlElement^ include;
					 for (int i=0; i<this->GetIncludeFolders()->Items->Count; i++) {
						 include = xd->CreateElement("Folder");
						 include->InnerText = this->GetIncludeFolders()->Items[i]->ToString();
						 innards->AppendChild(include);
					 }					 
				 }
				 child->AppendChild(innards);
				 root->AppendChild(child);
			 } else {
				 innards->InnerText = "no";
				 child->AppendChild(innards);
				 root->AppendChild(child);
			 }		

			 child = xd->CreateElement("Exclude");		
			 innards = xd->CreateElement("Enabled");	
			 if (this->GetExcludeFlag()) {				 
				 innards->InnerText = "yes";
				 child->AppendChild(innards);
				 innards = xd->CreateElement("Recurse");				  
				 innards->InnerText = ((this->GetExcludeRecurseFlag()) ? "yes" : "no");
				 child->AppendChild(innards);
				 innards = xd->CreateElement("FolderList");				 
				 if (this->GetExcludeFolders()->Items->Count > 0) {
					 XmlElement^ exclude;
					 for (int i=0; i<this->GetExcludeFolders()->Items->Count; i++) {
						 exclude = xd->CreateElement("Folder");
						 exclude->InnerText = this->GetExcludeFolders()->Items[i]->ToString();
						 innards->AppendChild(exclude);
					 }					 
				 }
				 child->AppendChild(innards);
				 root->AppendChild(child);
			 } else {
				 innards->InnerText = "no";
				 child->AppendChild(innards);
				 root->AppendChild(child);
			 }	
			 
			 child = xd->CreateElement("KeywordList");
			 XmlElement^ keyword;
			 for (int i=0; i<this->GetSearchKeys()->Items->Count; i++) {
				 keyword = xd->CreateElement("Keyword");
				 keyword->InnerText = this->GetSearchKeys()->Items[i]->ToString();
				 child->AppendChild(keyword);
			 }	
			 root->AppendChild(child);

			 child = xd->CreateElement("AnalyzeData");
			 child->InnerText = ((this->GetIsDesignOnly()) ? "no" : "yes");
			 root->AppendChild(child);

			 child = xd->CreateElement("ExactMatch");
			 child->InnerText = ((this->GetIsExactMatch()) ? "yes" : "no");
			 root->AppendChild(child);

			 child = xd->CreateElement("AutoLaunch");
			 child->InnerText = ((this->IsAutoLaunching) ? "yes" : "no");
			 root->AppendChild(child);
			 
			 xd->AppendChild(root);

			 // write xml
			 this->UpdateStatusField("Saved settings to:  " + file);
			 XmlTextWriter ^writer = gcnew XmlTextWriter(file, System::Text::Encoding::UTF8);
			 xd->WriteTo(writer);
			 writer->Close();	
}
