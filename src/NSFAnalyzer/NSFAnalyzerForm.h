#pragma once

#include "ListboxHandler.h"
#include "About.h"
#include "search_core.h"
#include "dlgServerList.h"
#include "dlgDatabaseList.h"
#include "configuration.h"

namespace NSFAnalyzer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class NSFAnalyzerForm : public System::Windows::Forms::Form {
	private: ListboxHandler m_lbxHandler;

	private: System::Windows::Forms::Label^  lblLeaveBlank;

	private: System::Windows::Forms::TextBox^  txtSsDatabase;
	private: System::Windows::Forms::Button^  btnSsServer;
	private: System::Windows::Forms::TextBox^  txtSsServer;
	private: System::Windows::Forms::Label^  lblSsDatabase;
	private: System::Windows::Forms::Label^  lblSsServer;
	private: System::Windows::Forms::Label^  lblScanDb;

	private: System::Windows::Forms::RadioButton^  rbDesignOnly;
	private: System::Windows::Forms::RadioButton^  rbAnalyzeData;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  saveSettingsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  closeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  logsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openErrorLogToolStripMenuItem;
	private: System::Windows::Forms::CheckBox^  chkExactMatch;
	private: System::Windows::Forms::ListBox^  lbxStatus;
	private: System::Windows::Forms::Button^  btnClearStatus;
	private: System::Windows::Forms::ToolStripMenuItem^  deleteLogsToolStripMenuItem;
	private: System::Windows::Forms::Button^  btnCancelSearch;
	private: System::ComponentModel::BackgroundWorker^  bgWorker;
	private: System::Windows::Forms::TextBox^  txtScanProgress;
	private: System::Windows::Forms::TextBox^  txtCurrentActivity;

	private: System::Windows::Forms::Label^  lblCurrentActivity;
	private: System::Windows::Forms::Label^  lblMatches;
	private: System::Windows::Forms::ToolStripMenuItem^  openOutputFileToolStripMenuItem;
	private: System::Windows::Forms::TabControl^  tabFolderOptions;
	private: System::Windows::Forms::TabPage^  tabpgInclude;
	private: System::Windows::Forms::Button^  btnRemoveInclude;
	private: System::Windows::Forms::Button^  btnAddInclude;
	private: System::Windows::Forms::TextBox^  txtInclude;
	private: System::Windows::Forms::ListBox^  lbxInclude;
	private: System::Windows::Forms::CheckBox^  chkRecurseInclude;
	private: System::Windows::Forms::CheckBox^  chkInclude;
	private: System::Windows::Forms::TabPage^  tabpgExclude;
	private: System::Windows::Forms::Button^  btnRemoveExclude;
	private: System::Windows::Forms::CheckBox^  chkRecurseExclude;
	private: System::Windows::Forms::Button^  btnAddExclude;
	private: System::Windows::Forms::TextBox^  txtExclude;
	private: System::Windows::Forms::ListBox^  lbxExclude;
	private: System::Windows::Forms::CheckBox^  chkExclude;
	private: System::Windows::Forms::CheckBox^  chkAutoOpen;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;

	private: System::Windows::Forms::SaveFileDialog^  sfdOutputFile;
	private: System::Windows::Forms::Button^  btnShowDetails;
	private: System::Windows::Forms::Button^  btnSsDatabase2;







































	private: NSFAnalyzerEngine^ m_nsf_analyze;
	private:
		void RefreshShowSearch() {
			this->btnSearch->Enabled = (this->txtOutputFile->Text->Length > 0 && this->lbxKeywords->Items->Count > 0 && this->txtSsServer->Text->Length > 0);
		}
	private:
		NSFAnalyzer::ConfigurationTool^ GetCurrentSettings(void) {
			ConfigurationTool^ cfg = gcnew ConfigurationTool();	
			cfg->SetStatusField(this->lbxStatus);
			cfg->SetFileFormat((this->rbHtml->Checked) ? "html" : "csv");
			cfg->SetFilePath(this->txtOutputFile->Text);
			cfg->SetServer(this->txtSsServer->Text);
			cfg->SetDatabase(this->txtSsDatabase->Text);
			cfg->SetIncludeFlag(this->chkInclude->Checked);
			cfg->SetExcludeFlag(this->chkExclude->Checked);
			cfg->SetIncludeRecurseFlag(this->chkRecurseInclude->Checked);
			cfg->SetExcludeRecurseFlag(this->chkRecurseExclude->Checked);
			cfg->SetIsDesignOnly(this->rbDesignOnly->Checked);
			cfg->SetIsExactMatch(this->chkExactMatch->Checked);
			cfg->SetIncludeFolders(this->lbxInclude);
			cfg->SetExcludeFolders(this->lbxExclude);			
			cfg->SetSearchKeys(this->lbxKeywords);
			cfg->IsAutoLaunching = this->chkAutoOpen->Checked;
			
			return cfg;
		}
	public:
		NSFAnalyzerForm()
		{
			InitializeComponent();
			
			this->m_nsf_analyze = gcnew NSFAnalyzerEngine();
			//
			//TODO: Add the constructor code here
			//
		}	

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~NSFAnalyzerForm()
		{

			if (components)
			{
				delete components;
			}
			
			if (this->m_nsf_analyze) { 					
				delete this->m_nsf_analyze;
			}

		}

	private: System::Windows::Forms::RadioButton^  rbHtml;
	private: System::Windows::Forms::RadioButton^  rbCsv;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;

	private: System::Windows::Forms::TextBox^  txtOutputFile;
	private: System::Windows::Forms::Button^  btnOutputFile;
	private: System::Windows::Forms::GroupBox^  groupBox1;





	private: System::Windows::Forms::Button^  btnAddKeyword;
	private: System::Windows::Forms::TextBox^  txtKeyword;
	private: System::Windows::Forms::ListBox^  lbxKeywords;
	private: System::Windows::Forms::Label^  lblKeywords;
	private: System::Windows::Forms::Button^  btnRemoveKeyword;








	private: System::Windows::Forms::Button^  btnSearch;

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(NSFAnalyzerForm::typeid));
			this->rbHtml = (gcnew System::Windows::Forms::RadioButton());
			this->rbCsv = (gcnew System::Windows::Forms::RadioButton());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->txtOutputFile = (gcnew System::Windows::Forms::TextBox());
			this->btnOutputFile = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->btnSsDatabase2 = (gcnew System::Windows::Forms::Button());
			this->chkAutoOpen = (gcnew System::Windows::Forms::CheckBox());
			this->tabFolderOptions = (gcnew System::Windows::Forms::TabControl());
			this->tabpgInclude = (gcnew System::Windows::Forms::TabPage());
			this->btnRemoveInclude = (gcnew System::Windows::Forms::Button());
			this->btnAddInclude = (gcnew System::Windows::Forms::Button());
			this->txtInclude = (gcnew System::Windows::Forms::TextBox());
			this->lbxInclude = (gcnew System::Windows::Forms::ListBox());
			this->chkRecurseInclude = (gcnew System::Windows::Forms::CheckBox());
			this->chkInclude = (gcnew System::Windows::Forms::CheckBox());
			this->tabpgExclude = (gcnew System::Windows::Forms::TabPage());
			this->btnRemoveExclude = (gcnew System::Windows::Forms::Button());
			this->chkRecurseExclude = (gcnew System::Windows::Forms::CheckBox());
			this->btnAddExclude = (gcnew System::Windows::Forms::Button());
			this->txtExclude = (gcnew System::Windows::Forms::TextBox());
			this->lbxExclude = (gcnew System::Windows::Forms::ListBox());
			this->chkExclude = (gcnew System::Windows::Forms::CheckBox());
			this->btnCancelSearch = (gcnew System::Windows::Forms::Button());
			this->chkExactMatch = (gcnew System::Windows::Forms::CheckBox());
			this->rbAnalyzeData = (gcnew System::Windows::Forms::RadioButton());
			this->rbDesignOnly = (gcnew System::Windows::Forms::RadioButton());
			this->lblLeaveBlank = (gcnew System::Windows::Forms::Label());
			this->btnSearch = (gcnew System::Windows::Forms::Button());
			this->txtSsDatabase = (gcnew System::Windows::Forms::TextBox());
			this->btnSsServer = (gcnew System::Windows::Forms::Button());
			this->btnRemoveKeyword = (gcnew System::Windows::Forms::Button());
			this->txtSsServer = (gcnew System::Windows::Forms::TextBox());
			this->btnAddKeyword = (gcnew System::Windows::Forms::Button());
			this->lblSsDatabase = (gcnew System::Windows::Forms::Label());
			this->txtKeyword = (gcnew System::Windows::Forms::TextBox());
			this->lblSsServer = (gcnew System::Windows::Forms::Label());
			this->lbxKeywords = (gcnew System::Windows::Forms::ListBox());
			this->lblKeywords = (gcnew System::Windows::Forms::Label());
			this->lblScanDb = (gcnew System::Windows::Forms::Label());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveSettingsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openOutputFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->closeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->logsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openErrorLogToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deleteLogsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->lbxStatus = (gcnew System::Windows::Forms::ListBox());
			this->btnClearStatus = (gcnew System::Windows::Forms::Button());
			this->bgWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->txtScanProgress = (gcnew System::Windows::Forms::TextBox());
			this->txtCurrentActivity = (gcnew System::Windows::Forms::TextBox());
			this->lblCurrentActivity = (gcnew System::Windows::Forms::Label());
			this->lblMatches = (gcnew System::Windows::Forms::Label());
			this->sfdOutputFile = (gcnew System::Windows::Forms::SaveFileDialog());
			this->btnShowDetails = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			this->tabFolderOptions->SuspendLayout();
			this->tabpgInclude->SuspendLayout();
			this->tabpgExclude->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// rbHtml
			// 
			this->rbHtml->AutoSize = true;
			this->rbHtml->Checked = true;
			this->rbHtml->Location = System::Drawing::Point(128, 28);
			this->rbHtml->Name = L"rbHtml";
			this->rbHtml->Size = System::Drawing::Size(55, 17);
			this->rbHtml->TabIndex = 1;
			this->rbHtml->TabStop = true;
			this->rbHtml->Text = L"HTML";
			this->rbHtml->UseVisualStyleBackColor = true;
			this->rbHtml->CheckedChanged += gcnew System::EventHandler(this, &NSFAnalyzerForm::rbHtml_CheckedChanged);
			// 
			// rbCsv
			// 
			this->rbCsv->AutoSize = true;
			this->rbCsv->Location = System::Drawing::Point(189, 28);
			this->rbCsv->Name = L"rbCsv";
			this->rbCsv->Size = System::Drawing::Size(46, 17);
			this->rbCsv->TabIndex = 2;
			this->rbCsv->Text = L"CSV";
			this->rbCsv->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(13, 30);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(77, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Output Format:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(13, 55);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(96, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Output File Name*:";
			// 
			// txtOutputFile
			// 
			this->txtOutputFile->Location = System::Drawing::Point(128, 54);
			this->txtOutputFile->Name = L"txtOutputFile";
			this->txtOutputFile->ScrollBars = System::Windows::Forms::ScrollBars::Horizontal;
			this->txtOutputFile->Size = System::Drawing::Size(379, 20);
			this->txtOutputFile->TabIndex = 5;
			this->txtOutputFile->Text = L"c:\\mytest.html";
			// 
			// btnOutputFile
			// 
			this->btnOutputFile->Location = System::Drawing::Point(513, 50);
			this->btnOutputFile->Name = L"btnOutputFile";
			this->btnOutputFile->Size = System::Drawing::Size(75, 23);
			this->btnOutputFile->TabIndex = 6;
			this->btnOutputFile->Text = L"Select File";
			this->btnOutputFile->UseVisualStyleBackColor = true;
			this->btnOutputFile->Click += gcnew System::EventHandler(this, &NSFAnalyzerForm::btnOutputFile_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->btnSsDatabase2);
			this->groupBox1->Controls->Add(this->chkAutoOpen);
			this->groupBox1->Controls->Add(this->tabFolderOptions);
			this->groupBox1->Controls->Add(this->btnCancelSearch);
			this->groupBox1->Controls->Add(this->chkExactMatch);
			this->groupBox1->Controls->Add(this->rbAnalyzeData);
			this->groupBox1->Controls->Add(this->rbDesignOnly);
			this->groupBox1->Controls->Add(this->lblLeaveBlank);
			this->groupBox1->Controls->Add(this->btnSearch);
			this->groupBox1->Controls->Add(this->txtSsDatabase);
			this->groupBox1->Controls->Add(this->btnSsServer);
			this->groupBox1->Controls->Add(this->btnRemoveKeyword);
			this->groupBox1->Controls->Add(this->txtSsServer);
			this->groupBox1->Controls->Add(this->btnAddKeyword);
			this->groupBox1->Controls->Add(this->lblSsDatabase);
			this->groupBox1->Controls->Add(this->txtKeyword);
			this->groupBox1->Controls->Add(this->lblSsServer);
			this->groupBox1->Controls->Add(this->lbxKeywords);
			this->groupBox1->Controls->Add(this->lblKeywords);
			this->groupBox1->Location = System::Drawing::Point(16, 86);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(709, 325);
			this->groupBox1->TabIndex = 7;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Search Criteria";
			// 
			// btnSsDatabase2
			// 
			this->btnSsDatabase2->Location = System::Drawing::Point(534, 49);
			this->btnSsDatabase2->Name = L"btnSsDatabase2";
			this->btnSsDatabase2->Size = System::Drawing::Size(29, 20);
			this->btnSsDatabase2->TabIndex = 26;
			this->btnSsDatabase2->Text = L"...";
			this->btnSsDatabase2->UseVisualStyleBackColor = true;
			this->btnSsDatabase2->Click += gcnew System::EventHandler(this, &NSFAnalyzerForm::btnSsDatabase2_Click);
			// 
			// chkAutoOpen
			// 
			this->chkAutoOpen->AutoSize = true;
			this->chkAutoOpen->Checked = true;
			this->chkAutoOpen->CheckState = System::Windows::Forms::CheckState::Checked;
			this->chkAutoOpen->Location = System::Drawing::Point(339, 288);
			this->chkAutoOpen->Name = L"chkAutoOpen";
			this->chkAutoOpen->Size = System::Drawing::Size(196, 17);
			this->chkAutoOpen->TabIndex = 24;
			this->chkAutoOpen->Text = L"Auto-launch output file after analysis";
			this->chkAutoOpen->UseVisualStyleBackColor = true;
			this->chkAutoOpen->CheckedChanged += gcnew System::EventHandler(this, &NSFAnalyzerForm::chkAutoOpen_CheckedChanged);
			// 
			// tabFolderOptions
			// 
			this->tabFolderOptions->Appearance = System::Windows::Forms::TabAppearance::FlatButtons;
			this->tabFolderOptions->Controls->Add(this->tabpgInclude);
			this->tabFolderOptions->Controls->Add(this->tabpgExclude);
			this->tabFolderOptions->Location = System::Drawing::Point(339, 96);
			this->tabFolderOptions->Name = L"tabFolderOptions";
			this->tabFolderOptions->SelectedIndex = 0;
			this->tabFolderOptions->ShowToolTips = true;
			this->tabFolderOptions->Size = System::Drawing::Size(346, 165);
			this->tabFolderOptions->TabIndex = 23;
			// 
			// tabpgInclude
			// 
			this->tabpgInclude->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->tabpgInclude->Controls->Add(this->btnRemoveInclude);
			this->tabpgInclude->Controls->Add(this->btnAddInclude);
			this->tabpgInclude->Controls->Add(this->txtInclude);
			this->tabpgInclude->Controls->Add(this->lbxInclude);
			this->tabpgInclude->Controls->Add(this->chkRecurseInclude);
			this->tabpgInclude->Controls->Add(this->chkInclude);
			this->tabpgInclude->Location = System::Drawing::Point(4, 25);
			this->tabpgInclude->Name = L"tabpgInclude";
			this->tabpgInclude->Padding = System::Windows::Forms::Padding(3);
			this->tabpgInclude->Size = System::Drawing::Size(338, 136);
			this->tabpgInclude->TabIndex = 0;
			this->tabpgInclude->Text = L"Include";
			this->tabpgInclude->ToolTipText = L"File directories to include";
			this->tabpgInclude->UseVisualStyleBackColor = true;
			// 
			// btnRemoveInclude
			// 
			this->btnRemoveInclude->Enabled = false;
			this->btnRemoveInclude->Location = System::Drawing::Point(246, 73);
			this->btnRemoveInclude->Name = L"btnRemoveInclude";
			this->btnRemoveInclude->Size = System::Drawing::Size(55, 25);
			this->btnRemoveInclude->TabIndex = 28;
			this->btnRemoveInclude->Text = L"Remove";
			this->btnRemoveInclude->UseVisualStyleBackColor = true;
			this->btnRemoveInclude->Click += gcnew System::EventHandler(this, &NSFAnalyzerForm::btnRemoveInclude_Click);
			// 
			// btnAddInclude
			// 
			this->btnAddInclude->Enabled = false;
			this->btnAddInclude->Location = System::Drawing::Point(246, 104);
			this->btnAddInclude->Name = L"btnAddInclude";
			this->btnAddInclude->Size = System::Drawing::Size(55, 23);
			this->btnAddInclude->TabIndex = 27;
			this->btnAddInclude->Text = L"Add";
			this->btnAddInclude->UseVisualStyleBackColor = true;
			this->btnAddInclude->Click += gcnew System::EventHandler(this, &NSFAnalyzerForm::btnAddInclude_Click);
			// 
			// txtInclude
			// 
			this->txtInclude->Enabled = false;
			this->txtInclude->Location = System::Drawing::Point(6, 106);
			this->txtInclude->Name = L"txtInclude";
			this->txtInclude->Size = System::Drawing::Size(234, 20);
			this->txtInclude->TabIndex = 26;
			this->txtInclude->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &NSFAnalyzerForm::txtInclude_KeyDown);
			// 
			// lbxInclude
			// 
			this->lbxInclude->BackColor = System::Drawing::Color::WhiteSmoke;
			this->lbxInclude->Enabled = false;
			this->lbxInclude->FormattingEnabled = true;
			this->lbxInclude->Location = System::Drawing::Point(6, 33);
			this->lbxInclude->Name = L"lbxInclude";
			this->lbxInclude->SelectionMode = System::Windows::Forms::SelectionMode::MultiSimple;
			this->lbxInclude->Size = System::Drawing::Size(234, 69);
			this->lbxInclude->TabIndex = 25;
			this->lbxInclude->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &NSFAnalyzerForm::lbxInclude_KeyDown);
			// 
			// chkRecurseInclude
			// 
			this->chkRecurseInclude->AutoSize = true;
			this->chkRecurseInclude->Location = System::Drawing::Point(76, 10);
			this->chkRecurseInclude->Name = L"chkRecurseInclude";
			this->chkRecurseInclude->Size = System::Drawing::Size(136, 17);
			this->chkRecurseInclude->TabIndex = 24;
			this->chkRecurseInclude->Text = L"Recurse Subdirectories";
			this->chkRecurseInclude->UseVisualStyleBackColor = true;
			this->chkRecurseInclude->Visible = false;
			// 
			// chkInclude
			// 
			this->chkInclude->AutoSize = true;
			this->chkInclude->Location = System::Drawing::Point(6, 10);
			this->chkInclude->Name = L"chkInclude";
			this->chkInclude->Size = System::Drawing::Size(64, 17);
			this->chkInclude->TabIndex = 23;
			this->chkInclude->Text = L"Include:";
			this->chkInclude->UseVisualStyleBackColor = true;
			this->chkInclude->CheckedChanged += gcnew System::EventHandler(this, &NSFAnalyzerForm::chkInclude_CheckedChanged);
			// 
			// tabpgExclude
			// 
			this->tabpgExclude->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->tabpgExclude->Controls->Add(this->btnRemoveExclude);
			this->tabpgExclude->Controls->Add(this->chkRecurseExclude);
			this->tabpgExclude->Controls->Add(this->btnAddExclude);
			this->tabpgExclude->Controls->Add(this->txtExclude);
			this->tabpgExclude->Controls->Add(this->lbxExclude);
			this->tabpgExclude->Controls->Add(this->chkExclude);
			this->tabpgExclude->Location = System::Drawing::Point(4, 25);
			this->tabpgExclude->Name = L"tabpgExclude";
			this->tabpgExclude->Padding = System::Windows::Forms::Padding(3);
			this->tabpgExclude->Size = System::Drawing::Size(338, 136);
			this->tabpgExclude->TabIndex = 1;
			this->tabpgExclude->Text = L"Exclude";
			this->tabpgExclude->ToolTipText = L"File directories to exclude";
			this->tabpgExclude->UseVisualStyleBackColor = true;
			// 
			// btnRemoveExclude
			// 
			this->btnRemoveExclude->Enabled = false;
			this->btnRemoveExclude->Location = System::Drawing::Point(246, 73);
			this->btnRemoveExclude->Name = L"btnRemoveExclude";
			this->btnRemoveExclude->Size = System::Drawing::Size(55, 25);
			this->btnRemoveExclude->TabIndex = 24;
			this->btnRemoveExclude->Text = L"Remove";
			this->btnRemoveExclude->UseVisualStyleBackColor = true;
			this->btnRemoveExclude->Click += gcnew System::EventHandler(this, &NSFAnalyzerForm::btnRemoveExclude_Click);
			// 
			// chkRecurseExclude
			// 
			this->chkRecurseExclude->AutoSize = true;
			this->chkRecurseExclude->Location = System::Drawing::Point(76, 10);
			this->chkRecurseExclude->Name = L"chkRecurseExclude";
			this->chkRecurseExclude->Size = System::Drawing::Size(136, 17);
			this->chkRecurseExclude->TabIndex = 20;
			this->chkRecurseExclude->Text = L"Recurse Subdirectories";
			this->chkRecurseExclude->UseVisualStyleBackColor = true;
			this->chkRecurseExclude->Visible = false;
			// 
			// btnAddExclude
			// 
			this->btnAddExclude->Enabled = false;
			this->btnAddExclude->Location = System::Drawing::Point(246, 104);
			this->btnAddExclude->Name = L"btnAddExclude";
			this->btnAddExclude->Size = System::Drawing::Size(55, 23);
			this->btnAddExclude->TabIndex = 23;
			this->btnAddExclude->Text = L"Add";
			this->btnAddExclude->UseVisualStyleBackColor = true;
			this->btnAddExclude->Click += gcnew System::EventHandler(this, &NSFAnalyzerForm::btnAddExclude_Click);
			// 
			// txtExclude
			// 
			this->txtExclude->Enabled = false;
			this->txtExclude->Location = System::Drawing::Point(6, 106);
			this->txtExclude->Name = L"txtExclude";
			this->txtExclude->Size = System::Drawing::Size(234, 20);
			this->txtExclude->TabIndex = 22;
			this->txtExclude->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &NSFAnalyzerForm::txtExclude_KeyDown);
			// 
			// lbxExclude
			// 
			this->lbxExclude->Enabled = false;
			this->lbxExclude->FormattingEnabled = true;
			this->lbxExclude->Location = System::Drawing::Point(6, 33);
			this->lbxExclude->Name = L"lbxExclude";
			this->lbxExclude->SelectionMode = System::Windows::Forms::SelectionMode::MultiSimple;
			this->lbxExclude->Size = System::Drawing::Size(234, 69);
			this->lbxExclude->TabIndex = 21;
			this->lbxExclude->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &NSFAnalyzerForm::lbxExclude_KeyDown);
			// 
			// chkExclude
			// 
			this->chkExclude->AutoSize = true;
			this->chkExclude->Location = System::Drawing::Point(6, 10);
			this->chkExclude->Name = L"chkExclude";
			this->chkExclude->Size = System::Drawing::Size(67, 17);
			this->chkExclude->TabIndex = 19;
			this->chkExclude->Text = L"Exclude:";
			this->chkExclude->UseVisualStyleBackColor = true;
			this->chkExclude->CheckedChanged += gcnew System::EventHandler(this, &NSFAnalyzerForm::chkExclude_CheckedChanged);
			// 
			// btnCancelSearch
			// 
			this->btnCancelSearch->BackColor = System::Drawing::SystemColors::Control;
			this->btnCancelSearch->Enabled = false;
			this->btnCancelSearch->Location = System::Drawing::Point(18, 287);
			this->btnCancelSearch->Name = L"btnCancelSearch";
			this->btnCancelSearch->Size = System::Drawing::Size(123, 23);
			this->btnCancelSearch->TabIndex = 20;
			this->btnCancelSearch->Text = L"Cancel Analysis";
			this->btnCancelSearch->UseVisualStyleBackColor = false;
			this->btnCancelSearch->Click += gcnew System::EventHandler(this, &NSFAnalyzerForm::btnCancelSearch_Click);
			// 
			// chkExactMatch
			// 
			this->chkExactMatch->AutoSize = true;
			this->chkExactMatch->Checked = true;
			this->chkExactMatch->CheckState = System::Windows::Forms::CheckState::Checked;
			this->chkExactMatch->Location = System::Drawing::Point(339, 265);
			this->chkExactMatch->Name = L"chkExactMatch";
			this->chkExactMatch->Size = System::Drawing::Size(146, 17);
			this->chkExactMatch->TabIndex = 19;
			this->chkExactMatch->Text = L"Ignore pre-compiled code";
			this->chkExactMatch->UseVisualStyleBackColor = true;
			// 
			// rbAnalyzeData
			// 
			this->rbAnalyzeData->AutoSize = true;
			this->rbAnalyzeData->CausesValidation = false;
			this->rbAnalyzeData->Location = System::Drawing::Point(541, 289);
			this->rbAnalyzeData->Name = L"rbAnalyzeData";
			this->rbAnalyzeData->Size = System::Drawing::Size(145, 17);
			this->rbAnalyzeData->TabIndex = 18;
			this->rbAnalyzeData->Text = L"Analyze Design and Data";
			this->rbAnalyzeData->UseVisualStyleBackColor = true;
			// 
			// rbDesignOnly
			// 
			this->rbDesignOnly->AutoSize = true;
			this->rbDesignOnly->CausesValidation = false;
			this->rbDesignOnly->Checked = true;
			this->rbDesignOnly->Location = System::Drawing::Point(541, 267);
			this->rbDesignOnly->Name = L"rbDesignOnly";
			this->rbDesignOnly->Size = System::Drawing::Size(122, 17);
			this->rbDesignOnly->TabIndex = 17;
			this->rbDesignOnly->TabStop = true;
			this->rbDesignOnly->Text = L"Analyze Design Only";
			this->rbDesignOnly->UseVisualStyleBackColor = true;
			// 
			// lblLeaveBlank
			// 
			this->lblLeaveBlank->AutoSize = true;
			this->lblLeaveBlank->Location = System::Drawing::Point(74, 72);
			this->lblLeaveBlank->Name = L"lblLeaveBlank";
			this->lblLeaveBlank->Size = System::Drawing::Size(220, 13);
			this->lblLeaveBlank->TabIndex = 16;
			this->lblLeaveBlank->Text = L"Leave database blank to search all on server";
			// 
			// btnSearch
			// 
			this->btnSearch->BackColor = System::Drawing::SystemColors::Control;
			this->btnSearch->Enabled = false;
			this->btnSearch->Location = System::Drawing::Point(18, 258);
			this->btnSearch->Name = L"btnSearch";
			this->btnSearch->Size = System::Drawing::Size(123, 23);
			this->btnSearch->TabIndex = 15;
			this->btnSearch->Text = L"Analyze Database(s)";
			this->btnSearch->UseVisualStyleBackColor = false;
			this->btnSearch->Click += gcnew System::EventHandler(this, &NSFAnalyzerForm::btnSearch_Click);
			// 
			// txtSsDatabase
			// 
			this->txtSsDatabase->Location = System::Drawing::Point(77, 49);
			this->txtSsDatabase->Name = L"txtSsDatabase";
			this->txtSsDatabase->Size = System::Drawing::Size(451, 20);
			this->txtSsDatabase->TabIndex = 4;
			// 
			// btnSsServer
			// 
			this->btnSsServer->Location = System::Drawing::Point(534, 18);
			this->btnSsServer->Name = L"btnSsServer";
			this->btnSsServer->Size = System::Drawing::Size(29, 20);
			this->btnSsServer->TabIndex = 3;
			this->btnSsServer->Text = L"...";
			this->btnSsServer->UseVisualStyleBackColor = true;
			this->btnSsServer->Click += gcnew System::EventHandler(this, &NSFAnalyzerForm::btnSsServer_Click);
			// 
			// btnRemoveKeyword
			// 
			this->btnRemoveKeyword->Location = System::Drawing::Point(264, 199);
			this->btnRemoveKeyword->Name = L"btnRemoveKeyword";
			this->btnRemoveKeyword->Size = System::Drawing::Size(55, 23);
			this->btnRemoveKeyword->TabIndex = 14;
			this->btnRemoveKeyword->Text = L"Remove";
			this->btnRemoveKeyword->UseVisualStyleBackColor = true;
			this->btnRemoveKeyword->Click += gcnew System::EventHandler(this, &NSFAnalyzerForm::btnRemoveKeyword_Click);
			// 
			// txtSsServer
			// 
			this->txtSsServer->Location = System::Drawing::Point(77, 19);
			this->txtSsServer->Name = L"txtSsServer";
			this->txtSsServer->Size = System::Drawing::Size(451, 20);
			this->txtSsServer->TabIndex = 2;
			this->txtSsServer->TextChanged += gcnew System::EventHandler(this, &NSFAnalyzerForm::txtSsServer_TextChanged);
			// 
			// btnAddKeyword
			// 
			this->btnAddKeyword->Location = System::Drawing::Point(264, 228);
			this->btnAddKeyword->Name = L"btnAddKeyword";
			this->btnAddKeyword->Size = System::Drawing::Size(55, 23);
			this->btnAddKeyword->TabIndex = 13;
			this->btnAddKeyword->Text = L"Add";
			this->btnAddKeyword->UseVisualStyleBackColor = true;
			this->btnAddKeyword->Click += gcnew System::EventHandler(this, &NSFAnalyzerForm::btnAddKeyword_Click);
			// 
			// lblSsDatabase
			// 
			this->lblSsDatabase->AutoSize = true;
			this->lblSsDatabase->Location = System::Drawing::Point(15, 53);
			this->lblSsDatabase->Name = L"lblSsDatabase";
			this->lblSsDatabase->Size = System::Drawing::Size(56, 13);
			this->lblSsDatabase->TabIndex = 1;
			this->lblSsDatabase->Text = L"Database:";
			// 
			// txtKeyword
			// 
			this->txtKeyword->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->txtKeyword->ForeColor = System::Drawing::Color::Red;
			this->txtKeyword->Location = System::Drawing::Point(18, 228);
			this->txtKeyword->Name = L"txtKeyword";
			this->txtKeyword->Size = System::Drawing::Size(240, 20);
			this->txtKeyword->TabIndex = 12;
			this->txtKeyword->Text = L">> Enter Search Keywords Here <<";
			this->txtKeyword->Enter += gcnew System::EventHandler(this, &NSFAnalyzerForm::txtKeyword_Enter);
			this->txtKeyword->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &NSFAnalyzerForm::txtKeyword_KeyDown);
			// 
			// lblSsServer
			// 
			this->lblSsServer->AutoSize = true;
			this->lblSsServer->Location = System::Drawing::Point(15, 22);
			this->lblSsServer->Name = L"lblSsServer";
			this->lblSsServer->Size = System::Drawing::Size(45, 13);
			this->lblSsServer->TabIndex = 0;
			this->lblSsServer->Text = L"Server*:";
			// 
			// lbxKeywords
			// 
			this->lbxKeywords->BackColor = System::Drawing::Color::WhiteSmoke;
			this->lbxKeywords->FormattingEnabled = true;
			this->lbxKeywords->Location = System::Drawing::Point(18, 127);
			this->lbxKeywords->Name = L"lbxKeywords";
			this->lbxKeywords->SelectionMode = System::Windows::Forms::SelectionMode::MultiSimple;
			this->lbxKeywords->Size = System::Drawing::Size(240, 95);
			this->lbxKeywords->TabIndex = 11;
			this->lbxKeywords->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &NSFAnalyzerForm::lbxKeywords_KeyDown);
			// 
			// lblKeywords
			// 
			this->lblKeywords->AutoSize = true;
			this->lblKeywords->Location = System::Drawing::Point(6, 105);
			this->lblKeywords->Name = L"lblKeywords";
			this->lblKeywords->Size = System::Drawing::Size(97, 13);
			this->lblKeywords->TabIndex = 10;
			this->lblKeywords->Text = L"Search Keywords*:";
			// 
			// lblScanDb
			// 
			this->lblScanDb->AutoSize = true;
			this->lblScanDb->Location = System::Drawing::Point(13, 422);
			this->lblScanDb->Name = L"lblScanDb";
			this->lblScanDb->Size = System::Drawing::Size(93, 13);
			this->lblScanDb->TabIndex = 9;
			this->lblScanDb->Text = L"Current Database:";
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->toolStripMenuItem1, 
				this->logsToolStripMenuItem, this->helpToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
			this->menuStrip1->Size = System::Drawing::Size(769, 24);
			this->menuStrip1->TabIndex = 10;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->saveSettingsToolStripMenuItem, 
				this->openOutputFileToolStripMenuItem, this->closeToolStripMenuItem});
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(37, 20);
			this->toolStripMenuItem1->Text = L"&File";
			// 
			// saveSettingsToolStripMenuItem
			// 
			this->saveSettingsToolStripMenuItem->Name = L"saveSettingsToolStripMenuItem";
			this->saveSettingsToolStripMenuItem->Size = System::Drawing::Size(165, 22);
			this->saveSettingsToolStripMenuItem->Text = L"&Save Settings";
			this->saveSettingsToolStripMenuItem->Click += gcnew System::EventHandler(this, &NSFAnalyzerForm::saveSettingsToolStripMenuItem_Click);
			// 
			// openOutputFileToolStripMenuItem
			// 
			this->openOutputFileToolStripMenuItem->Name = L"openOutputFileToolStripMenuItem";
			this->openOutputFileToolStripMenuItem->Size = System::Drawing::Size(165, 22);
			this->openOutputFileToolStripMenuItem->Text = L"Open Output File";
			this->openOutputFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &NSFAnalyzerForm::openOutputFileToolStripMenuItem_Click);
			// 
			// closeToolStripMenuItem
			// 
			this->closeToolStripMenuItem->Name = L"closeToolStripMenuItem";
			this->closeToolStripMenuItem->Size = System::Drawing::Size(165, 22);
			this->closeToolStripMenuItem->Text = L"&Close";
			this->closeToolStripMenuItem->Click += gcnew System::EventHandler(this, &NSFAnalyzerForm::closeToolStripMenuItem_Click);
			// 
			// logsToolStripMenuItem
			// 
			this->logsToolStripMenuItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->logsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->openToolStripMenuItem, 
				this->openErrorLogToolStripMenuItem, this->deleteLogsToolStripMenuItem});
			this->logsToolStripMenuItem->Name = L"logsToolStripMenuItem";
			this->logsToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->logsToolStripMenuItem->Text = L"&Logs";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(161, 22);
			this->openToolStripMenuItem->Text = L"Open &Status Log";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &NSFAnalyzerForm::openToolStripMenuItem_Click);
			// 
			// openErrorLogToolStripMenuItem
			// 
			this->openErrorLogToolStripMenuItem->Name = L"openErrorLogToolStripMenuItem";
			this->openErrorLogToolStripMenuItem->Size = System::Drawing::Size(161, 22);
			this->openErrorLogToolStripMenuItem->Text = L"Open &Error Log";
			this->openErrorLogToolStripMenuItem->Click += gcnew System::EventHandler(this, &NSFAnalyzerForm::openErrorLogToolStripMenuItem_Click);
			// 
			// deleteLogsToolStripMenuItem
			// 
			this->deleteLogsToolStripMenuItem->Name = L"deleteLogsToolStripMenuItem";
			this->deleteLogsToolStripMenuItem->Size = System::Drawing::Size(161, 22);
			this->deleteLogsToolStripMenuItem->Text = L"Delete Logs";
			this->deleteLogsToolStripMenuItem->Click += gcnew System::EventHandler(this, &NSFAnalyzerForm::deleteLogsToolStripMenuItem_Click);
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->aboutToolStripMenuItem});
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->helpToolStripMenuItem->Text = L"&Help";
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(107, 22);
			this->aboutToolStripMenuItem->Text = L"&About";
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &NSFAnalyzerForm::aboutToolStripMenuItem_Click);
			// 
			// lbxStatus
			// 
			this->lbxStatus->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->lbxStatus->ForeColor = System::Drawing::Color::Maroon;
			this->lbxStatus->FormattingEnabled = true;
			this->lbxStatus->Location = System::Drawing::Point(64, 480);
			this->lbxStatus->Name = L"lbxStatus";
			this->lbxStatus->Size = System::Drawing::Size(637, 82);
			this->lbxStatus->TabIndex = 11;
			this->lbxStatus->Visible = false;
			// 
			// btnClearStatus
			// 
			this->btnClearStatus->Location = System::Drawing::Point(707, 539);
			this->btnClearStatus->Name = L"btnClearStatus";
			this->btnClearStatus->Size = System::Drawing::Size(55, 23);
			this->btnClearStatus->TabIndex = 12;
			this->btnClearStatus->Text = L"Clear";
			this->btnClearStatus->UseVisualStyleBackColor = true;
			this->btnClearStatus->Visible = false;
			this->btnClearStatus->Click += gcnew System::EventHandler(this, &NSFAnalyzerForm::btnClearStatus_Click);
			// 
			// bgWorker
			// 
			this->bgWorker->WorkerReportsProgress = true;
			this->bgWorker->WorkerSupportsCancellation = true;
			this->bgWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &NSFAnalyzerForm::bgWorker_DoWork);
			this->bgWorker->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &NSFAnalyzerForm::bgWorker_ProgressChanged);
			this->bgWorker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &NSFAnalyzerForm::bgWorker_RunWorkerCompleted);
			// 
			// txtScanProgress
			// 
			this->txtScanProgress->BackColor = System::Drawing::SystemColors::Control;
			this->txtScanProgress->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->txtScanProgress->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(64)), 
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->txtScanProgress->Location = System::Drawing::Point(108, 422);
			this->txtScanProgress->Name = L"txtScanProgress";
			this->txtScanProgress->Size = System::Drawing::Size(483, 13);
			this->txtScanProgress->TabIndex = 13;
			// 
			// txtCurrentActivity
			// 
			this->txtCurrentActivity->BackColor = System::Drawing::SystemColors::Control;
			this->txtCurrentActivity->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->txtCurrentActivity->ForeColor = System::Drawing::Color::Blue;
			this->txtCurrentActivity->Location = System::Drawing::Point(108, 451);
			this->txtCurrentActivity->Name = L"txtCurrentActivity";
			this->txtCurrentActivity->Size = System::Drawing::Size(483, 13);
			this->txtCurrentActivity->TabIndex = 15;
			// 
			// lblCurrentActivity
			// 
			this->lblCurrentActivity->AutoSize = true;
			this->lblCurrentActivity->Location = System::Drawing::Point(13, 451);
			this->lblCurrentActivity->Name = L"lblCurrentActivity";
			this->lblCurrentActivity->Size = System::Drawing::Size(44, 13);
			this->lblCurrentActivity->TabIndex = 14;
			this->lblCurrentActivity->Text = L"Activity:";
			// 
			// lblMatches
			// 
			this->lblMatches->AutoSize = true;
			this->lblMatches->Location = System::Drawing::Point(13, 480);
			this->lblMatches->Name = L"lblMatches";
			this->lblMatches->Size = System::Drawing::Size(45, 13);
			this->lblMatches->TabIndex = 16;
			this->lblMatches->Text = L"Results:";
			this->lblMatches->Visible = false;
			// 
			// sfdOutputFile
			// 
			this->sfdOutputFile->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &NSFAnalyzerForm::sfdOutputFile_FileOk);
			// 
			// btnShowDetails
			// 
			this->btnShowDetails->Location = System::Drawing::Point(597, 451);
			this->btnShowDetails->Name = L"btnShowDetails";
			this->btnShowDetails->Size = System::Drawing::Size(104, 23);
			this->btnShowDetails->TabIndex = 17;
			this->btnShowDetails->Text = L"Show Details  >>";
			this->btnShowDetails->UseVisualStyleBackColor = true;
			this->btnShowDetails->Click += gcnew System::EventHandler(this, &NSFAnalyzerForm::btnShowDetails_Click);
			// 
			// NSFAnalyzerForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(769, 575);
			this->Controls->Add(this->btnShowDetails);
			this->Controls->Add(this->lblMatches);
			this->Controls->Add(this->txtCurrentActivity);
			this->Controls->Add(this->lblCurrentActivity);
			this->Controls->Add(this->btnClearStatus);
			this->Controls->Add(this->lbxStatus);
			this->Controls->Add(this->lblScanDb);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->btnOutputFile);
			this->Controls->Add(this->txtOutputFile);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->rbCsv);
			this->Controls->Add(this->rbHtml);
			this->Controls->Add(this->menuStrip1);
			this->Controls->Add(this->txtScanProgress);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"NSFAnalyzerForm";
			this->Text = L"NSF Analyzer";
			this->Load += gcnew System::EventHandler(this, &NSFAnalyzerForm::NSFAnalyzerForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->tabFolderOptions->ResumeLayout(false);
			this->tabpgInclude->ResumeLayout(false);
			this->tabpgInclude->PerformLayout();
			this->tabpgExclude->ResumeLayout(false);
			this->tabpgExclude->PerformLayout();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
private: System::Void NSFAnalyzerForm_Load(System::Object^  sender, System::EventArgs^  e) {
				// load from config					 	
				this->txtCurrentActivity->Text = "Loading configuration settings...";
				int pos = Application::ExecutablePath->LastIndexOf("\\");
				String^ exePath = Application::ExecutablePath->Substring(0, pos);
				String^ xmlFilePath = exePath + "\\settings.xml";
				File::Delete(exePath + "\\scan_log.txt");
				File::Delete(exePath + "\\error_log.txt");
				ListBox^ lbx;

				ConfigurationTool^ cfg = gcnew ConfigurationTool();	
				if (cfg->Read(xmlFilePath)) {
					this->txtCurrentActivity->Text = "No previously saved configuration settings found.";
					return;
				}
				this->rbHtml->Checked = cfg->GetFileFormat()->Equals("html");
				this->txtOutputFile->Text = cfg->GetFilePath();
				this->txtSsServer->Text = cfg->GetServer();
				this->txtSsDatabase->Text = cfg->GetDatabase();
				this->chkInclude->Checked = cfg->GetIncludeFlag();
				this->chkExclude->Checked = cfg->GetExcludeFlag();				
				this->chkRecurseInclude->Checked = cfg->GetIncludeRecurseFlag();
				this->chkRecurseExclude->Checked = cfg->GetExcludeRecurseFlag();
				lbx = cfg->GetIncludeFolders();
				if (lbx) {
					for (int i=0; i<lbx->Items->Count; i++) {
						this->lbxInclude->Items->Add(lbx->Items[i]);
					}
				}
				
				lbx = cfg->GetExcludeFolders();
				if (lbx) {
					for (int i=0; i<lbx->Items->Count; i++) {
						this->lbxExclude->Items->Add(lbx->Items[i]);
					}
				}

				lbx = cfg->GetSearchKeys();
				if (lbx) {
					for (int i=0; i<lbx->Items->Count; i++) {
						this->lbxKeywords->Items->Add(lbx->Items[i]);
					}
				}
				this->chkAutoOpen->Checked = cfg->IsAutoLaunching;
				
				this->RefreshShowSearch();
				this->txtCurrentActivity->Text = "Configuration settings loaded...";
				this->Height = 600 - lbxStatus->Height - 5;
			 }

private: System::Void btnOutputFile_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->sfdOutputFile->Filter = ((this->rbHtml->Checked) ? L"HTML files (.html)|*.html|csv files (.csv)|*.csv" : L"CSV (Comma-separated files) (.csv)|*.csv|html files (.html)|*.html");
			 System::Windows::Forms::DialogResult result = this->sfdOutputFile->ShowDialog();
			 if (System::Windows::Forms::DialogResult::OK == result) {
				 this->txtOutputFile->Text = this->sfdOutputFile->FileName;
			 }
		 }

private: System::Void btnAddKeyword_Click(System::Object^  sender, System::EventArgs^  e) {	
			if (!this->txtKeyword->Text->Equals(L">> Enter Search Keywords Here <<"))
			{
				m_lbxHandler.AddItem(this->lbxKeywords, this->txtKeyword);	
				this->RefreshShowSearch();
			}
		 }
private: System::Void btnRemoveKeyword_Click(System::Object^  sender, System::EventArgs^  e) {
			 m_lbxHandler.RemoveSelectedItem(this->lbxKeywords);
			 this->RefreshShowSearch();
		 }

private: System::Void lbxKeywords_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if (e->KeyCode == System::Windows::Forms::Keys::Delete || e->KeyCode == System::Windows::Forms::Keys::Back) {
				 this->btnRemoveKeyword->PerformClick();
			 }
		 }
private: System::Void btnAddExclude_Click(System::Object^  sender, System::EventArgs^  e) {
			 m_lbxHandler.AddItem(lbxExclude, txtExclude);
		 }
private: System::Void btnRemoveExclude_Click(System::Object^  sender, System::EventArgs^  e) {
			 m_lbxHandler.RemoveSelectedItem(this->lbxExclude);
		 }

private: System::Void lbxExclude_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			if (e->KeyCode == System::Windows::Forms::Keys::Delete || e->KeyCode == System::Windows::Forms::Keys::Back) {
				 this->btnRemoveExclude->PerformClick();
			 }
		 }
private: System::Void btnAddInclude_Click(System::Object^  sender, System::EventArgs^  e) {
			 m_lbxHandler.AddItem(lbxInclude, txtInclude);
		 }
private: System::Void btnRemoveInclude_Click(System::Object^  sender, System::EventArgs^  e) {
			 m_lbxHandler.RemoveSelectedItem(lbxInclude);
		 }
private: System::Void lbxInclude_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if (e->KeyCode == System::Windows::Forms::Keys::Delete || e->KeyCode == System::Windows::Forms::Keys::Back) {
				 this->btnRemoveInclude->PerformClick();
			 }
		 }
private: System::Void txtKeyword_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if (e->KeyCode == System::Windows::Forms::Keys::Enter) {
				 this->btnAddKeyword->PerformClick();
			 }
		 }
private: System::Void txtExclude_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if (e->KeyCode == System::Windows::Forms::Keys::Enter) {
				 this->btnAddExclude->PerformClick();
			 }
		 }
private: System::Void txtInclude_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if (e->KeyCode == System::Windows::Forms::Keys::Enter) {
				 this->btnAddInclude->PerformClick();
			 }
		 }
private: System::Void chkExclude_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {			 
			 if (safe_cast<System::Windows::Forms::CheckBox^>(sender)->Checked) {
				 this->lbxExclude->Enabled = true;
				 this->txtExclude->Enabled = true;
				 this->btnAddExclude->Enabled = true;
				 this->btnRemoveExclude->Enabled = true;
				 this->chkRecurseExclude->Visible = true;

				 this->chkInclude->Checked = false;
				 this->lbxInclude->Enabled = false;
				 this->txtInclude->Enabled = false;
				 this->btnAddInclude->Enabled = false;
				 this->btnRemoveInclude->Enabled = false;				 
				 
			 } else {
				 this->lbxExclude->Enabled = false;
				 this->txtExclude->Enabled = false;
				 this->btnAddExclude->Enabled = false;
				 this->btnRemoveExclude->Enabled = false;
				 this->chkRecurseExclude->Visible = false;

				 this->lbxInclude->Enabled = true;
				 this->txtInclude->Enabled = true;
				 this->btnAddInclude->Enabled = true;
				 this->btnRemoveInclude->Enabled = true;				 

			 }
		 }

private: System::Void chkInclude_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (safe_cast<System::Windows::Forms::CheckBox^>(sender)->Checked) {
				 this->lbxInclude->Enabled = true;
				 this->txtInclude->Enabled = true;
				 this->btnAddInclude->Enabled = true;
				 this->btnRemoveInclude->Enabled = true;
				 this->chkRecurseInclude->Visible = true;

				 this->chkExclude->Checked = false;
				 this->lbxExclude->Enabled = false;
				 this->txtExclude->Enabled = false;
				 this->btnAddExclude->Enabled = false;
				 this->btnRemoveExclude->Enabled = false;				 
				 
			 } else {
				 this->lbxInclude->Enabled = false;
				 this->txtInclude->Enabled = false;
				 this->btnAddInclude->Enabled = false;
				 this->btnRemoveInclude->Enabled = false;	
				 this->chkRecurseInclude->Visible = false;

				 this->lbxExclude->Enabled = true;
				 this->txtExclude->Enabled = true;
				 this->btnAddExclude->Enabled = true;
				 this->btnRemoveExclude->Enabled = true;				 

			 }
		 }

private: System::Void btnSearch_Click(System::Object^  sender, System::EventArgs^  e) {			
			this->btnSearch->Enabled = false;
			this->btnCancelSearch->Enabled = true;
			this->txtCurrentActivity->Text = "Beginning Search...";			
			this->bgWorker->RunWorkerAsync();			
		}

private: System::Void btnSsServer_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->m_nsf_analyze->BindStatusField(this->lbxStatus);
			 dlgServerList^ dlgServer = gcnew dlgServerList(this->txtSsServer, this->btnSsServer);	
			 std::vector<string> serverNames(0);
			 this->m_nsf_analyze->GetServerList(serverNames);
	  		 dlgServer->setServers(serverNames);
		 	 this->btnSsServer->Enabled = false;
			 dlgServer->ShowDialog();
		 }

private: System::Void txtSsServer_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 this->RefreshShowSearch();
		 }
private: System::Void btnSsDatabase_Click(System::Object^  sender, System::EventArgs^  e) {		
			 /*
			 this->m_nsf_analyze->BindStatusField(this->lbxStatus);

			 if (this->txtSsServer->Text->Length == 0) {
				 this->txtSsServer->Text = L"Local";
			 }
			 dlgServerList^ dlgDatabaseList = gcnew dlgServerList(this->txtSsDatabase, this->btnSsDatabase, "Select a Database", "Select a database from the list below:");	
			 std::vector<string> databaseNames(0);
			 this->m_nsf_analyze->GetDatabaseList(this->txtSsServer->Text, databaseNames);
			 dlgDatabaseList->setServers(databaseNames);
			 this->btnSsDatabase->Enabled = false;
			 dlgDatabaseList->ShowDialog();	
			 */
		 }
private: System::Void closeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }
private: System::Void saveSettingsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			// Save configuration
			int pos = Application::ExecutablePath->LastIndexOf("\\");
			String^ exePath = Application::ExecutablePath->Substring(0, pos);
			String^ xmlFilePath = exePath + "\\settings.xml";

			// i wanted to pass this to the constructor originally, and not have a
			// class object representing the UI fields. However, I did not really want
			// to expose the fields as public objects. So to avoid making getters/setters,
			// i would need to use reflection to get to the properties of the active container control.
			// I am not a fan of this either, because though it takes away the need for a business object
			// representing my interface and reduces code, it would have been a somewhat cryptic approach
			ConfigurationTool^ cfg = this->GetCurrentSettings();

			// save to file system
			cfg->Write(xmlFilePath);			
			 
		 }
private: System::Void btnClearStatus_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->lbxStatus->Items->Clear();
		 }
private: System::Void deleteLogsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 	int pos = Application::ExecutablePath->LastIndexOf("\\");
				String^ exePath = Application::ExecutablePath->Substring(0, pos);				
				File::Delete(exePath + "\\scan_log.txt");
				File::Delete(exePath + "\\error_log.txt");
		 }
private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 int pos = Application::ExecutablePath->LastIndexOf("\\");
			 String^ exePath = Application::ExecutablePath->Substring(0, pos);
			 try {
				System::Diagnostics::Process::Start(exePath + "\\scan_log.txt");
			 } catch(System::Exception^) {
				 MessageBox::Show("The file: " + exePath + "\\scan_log.txt does not exist.\n\nNote: Log files are removed each time this tool is launched.", "Scan Log", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			 }
		 }
private: System::Void openErrorLogToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			int pos = Application::ExecutablePath->LastIndexOf("\\");
			String^ exePath = Application::ExecutablePath->Substring(0, pos);
			try {
			    System::Diagnostics::Process::Start(exePath + "\\error_log.txt");
			 } catch(System::Exception^) {
				MessageBox::Show("The file: " + exePath + "\\error_log.txt does not exist.\n\nNote: Log files are removed each time this tool is launched.", "Error Log", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			}
		 }

private: 
	System::Void bgWorker_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
		this->m_nsf_analyze->pThreadInitialize();	
		this->m_nsf_analyze->WorkThreadFired = true;
		ConfigurationTool^ cfg = this->GetCurrentSettings();
		this->m_nsf_analyze->BindConfiguration(cfg);
		this->m_nsf_analyze->BindThreadWorker(this->bgWorker);
		this->m_nsf_analyze->Search();
	}
private: 
	System::Void bgWorker_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {					
		this->btnSearch->Enabled = true;
		this->btnCancelSearch->Enabled = false;
		this->txtScanProgress->Text = "";
		this->txtCurrentActivity->Text = "";
		if (this->m_nsf_analyze->scanner->MatchCount > 0) {
			this->lbxStatus->Items->Insert(0, "Matches Found - see below:");
		} else {
			this->lbxStatus->Items->Insert(0, "No Matches Found");
		}
	}
private: 	
	System::Void bgWorker_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) {
		if (!String::IsNullOrEmpty(this->m_nsf_analyze->ProgressScanDatabase) && !this->m_nsf_analyze->ProgressScanDatabase->Equals(String::Empty)) {
			this->txtScanProgress->Text = this->m_nsf_analyze->ProgressScanDatabase;
		}
		if (!String::IsNullOrEmpty(this->m_nsf_analyze->ProgressCurrentActivity) && !this->m_nsf_analyze->ProgressCurrentActivity->Equals(String::Empty)) {
			this->txtCurrentActivity->Text = this->m_nsf_analyze->ProgressCurrentActivity;
		}
		if (!String::IsNullOrEmpty(this->m_nsf_analyze->ProgressMatch) && !this->m_nsf_analyze->ProgressMatch->Equals(String::Empty)) {
			if (this->m_nsf_analyze->ProgressMatch->IndexOf("¥") > 0) {
				cli::array<System::String^, 1>^ parts = this->m_nsf_analyze->ProgressMatch->Split('¥');
				for (int i=0; i<parts->Length; i++) {
					if (parts[0]!=String::Empty && parts[0]->Length > 0) {
						this->lbxStatus->Items->Insert(0, parts[0]);						
					}
				}
			} else {
				this->lbxStatus->Items->Insert(0, this->m_nsf_analyze->ProgressMatch);
			}
			this->m_nsf_analyze->ProgressMatch = "";
		}
	}
	
private: System::Void btnCancelSearch_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->bgWorker->CancelAsync();			 
		 }
private: System::Void openOutputFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (this->txtOutputFile->Text != String::Empty) {
				 try {
					System::Diagnostics::Process::Start(this->txtOutputFile->Text);
				 } catch (FileNotFoundException^) {
				 } catch (Exception^) {
				 }
			 }	
		 }


private: System::Void chkAutoOpen_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

			 About^ helpAbout = gcnew About();
			 helpAbout->ShowDialog();
			 return;
			 //Form^ helpAbout = gcnew Form();
			 String ^ version = System::Reflection::Assembly::GetExecutingAssembly()->GetName()->Version->ToString();
			 helpAbout->Text = "NSFAnalyzer";
			 Label^ lbl1 = gcnew Label;			 			 
			 lbl1->Text = "NSFAnalyzer version " + version + "\n\nCreated by T. Brian Nichols";
			 lbl1->Location = System::Drawing::Point( 10, 10 );
			 lbl1->Size = System::Drawing::Size( 250, 30 );
			 lbl1->AutoSize = true;

			 helpAbout->Controls->Add(lbl1);

			       // Create the LinkLabel.
			  LinkLabel^ lnkLbl1 = gcnew System::Windows::Forms::LinkLabel;

			  // Configure the LinkLabel's size and location. Specify that the
			  // size should be automatically determined by the content.
			  lnkLbl1->Location = System::Drawing::Point( 34, 56 );
			  lnkLbl1->Size = System::Drawing::Size( 224, 16 );
			  lnkLbl1->AutoSize = true;

			  // Configure the appearance.
			  lnkLbl1->DisabledLinkColor = System::Drawing::Color::Red;
			  lnkLbl1->VisitedLinkColor = System::Drawing::Color::Blue;
			  lnkLbl1->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			  lnkLbl1->LinkColor = System::Drawing::Color::Navy;
			  lnkLbl1->TabIndex = 0;
			  lnkLbl1->TabStop = true;
		
			  // Identify what the first Link is.
			  String^ el_email = "mailto://timothy_b_nichols@yahoo.com";
			  String^ il_email = "Email: timothy_b_nichols@yahoo.com";
			  String^ projectUrl = "http://www.openntf.org/internal/home.nsf/project.xsp?action=openDocument&name=NSFAnalyzer/";
			  lnkLbl1->LinkArea = LinkArea(8, il_email->Length+el_email->Length+1);

			  // Identify that the first link is visited already.
			  lnkLbl1->Links[0]->Visited = true;

			  // Set the Text property to a String*.
			  lnkLbl1->Text = il_email + " " + projectUrl;
			  lnkLbl1->Links[0]->LinkData = el_email;
			  lnkLbl1->Links->Add(el_email->Length+1, el_email->Length+1 + projectUrl->Length, projectUrl );
			  lnkLbl1->Links[1]->Enabled = true;
				array<Control^>^temp0 = {lnkLbl1};
				helpAbout->Controls->AddRange(temp0);
		  	  // Add an event handler to do something when the links are clicked.
			  lnkLbl1->LinkClicked += gcnew ::LinkLabelLinkClickedEventHandler( this, &NSFAnalyzerForm::lnkLbl1_LinkClicked );


		//	 helpAbout->FormBorderStyle = ::FormBorderStyle::FixedDialog;
		//	 helpAbout->SizeGripStyle = ::SizeGripStyle::Hide;
			 helpAbout->MinimizeBox = false;
			 helpAbout->MaximizeBox = false;
			 helpAbout->Size = System::Drawing::Size(250, 150);
			 helpAbout->ClientSize = System::Drawing::Size( 292, 266 );
			 helpAbout->AutoSize = true;
			 helpAbout->ShowDialog();
		 }

	private:
		void lnkLbl1_LinkClicked( Object^ /*sender*/, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e )
		{
			System::Windows::Forms::MessageBox::Show("yay");

		}

private: System::Void sfdOutputFile_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 this->RefreshShowSearch();			 
		 }
private: System::Void rbHtml_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (this->txtOutputFile->Text->Length > 0) {
				 int pos = this->txtOutputFile->Text->IndexOf(".");
				 if (pos > 0) {
					 int pos2 = -1;
					 if (this->rbCsv->Checked) {
						 pos2 = this->txtOutputFile->Text->ToLower()->LastIndexOf(".html");
						 if (pos2 > 0) {
							 this->txtOutputFile->Text = this->txtOutputFile->Text->ToLower()->Replace(".html", ".csv");
						 }
					 } else {
						 pos2 = this->txtOutputFile->Text->ToLower()->LastIndexOf(".csv");
						 if (pos2 > 0) {
							 this->txtOutputFile->Text = this->txtOutputFile->Text->ToLower()->Replace(".csv", ".html");
						 }
					 }
				 } else {
					 if (this->rbCsv->Checked) {
						this->txtOutputFile->Text += ".csv";
					 } else {
						 this->txtOutputFile->Text += ".html";
					 }
				 }
			 }
		 }
private: System::Void btnShowDetails_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (this->btnShowDetails->Text->Equals("Show Details  >>")) {
				 this->btnShowDetails->Text = "Hide Details  <<";
				 this->lblMatches->Visible = true;
				 this->lbxStatus->Visible = true;
				 this->btnClearStatus->Visible = true;
				 this->Height = 600;
			 } else {
				 this->btnShowDetails->Text = "Show Details  >>";
				 this->lblMatches->Visible = false;
				 this->lbxStatus->Visible = false;
				 this->btnClearStatus->Visible = false;
				 this->Height = 600 - lbxStatus->Height - 5;
			 }			 
		 }

private: System::Void btnSsDatabase2_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->m_nsf_analyze->BindStatusField(this->lbxStatus);

			 if (this->txtSsServer->Text->Length == 0) {
				 this->txtSsServer->Text = L"Local";
			 }
			 dlgDatabaseList^ dlgDbList = gcnew dlgDatabaseList(this->txtSsDatabase, this->btnSsDatabase2, "Select a Database", "Select a database from the list below:");	
			 std::vector<string> databaseNames(0);
			 this->m_nsf_analyze->GetDatabaseList(this->txtSsServer->Text, databaseNames);
			 dlgDbList->setDatabases(databaseNames);
			 this->btnSsDatabase2->Enabled = false;
			 dlgDbList->ShowDialog();	
		 }

private: System::Void txtKeyword_Enter(System::Object^  sender, System::EventArgs^  e) {
			 if (this->txtKeyword->Text->Equals(L">> Enter Search Keywords Here <<"))
			 {
				 System::Drawing::Font ^font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25, System::Drawing::FontStyle::Regular);
				 this->txtKeyword->Text = L"";	
				 this->txtKeyword->Font = font;
				 this->txtKeyword->ForeColor = System::Drawing::Color::Black;
			 }
		 }
};

}

