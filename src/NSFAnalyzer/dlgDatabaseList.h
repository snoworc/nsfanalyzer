#pragma once
#include <iostream>
#include <vector>
using namespace std;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace NSFAnalyzer {

	/// <summary>
	/// Summary for dlgDatabaseList
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class dlgDatabaseList : public System::Windows::Forms::Form
	{
	private:
		TextBox^ m_retTextBox;
	private: System::Windows::Forms::Label^  lblDialog;
	private: System::Windows::Forms::Button^  btnOk;


			 Button^ m_retButton;

	public:
		dlgDatabaseList(void) {
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		dlgDatabaseList(TextBox^ tb, Button^ btn) {
			InitializeComponent();
		
			m_retTextBox = tb;	
			m_retButton = btn;
		}
		dlgDatabaseList(TextBox^ tb, Button^ btn, String^ overrideCaption, String^ overrideLabel) {
			InitializeComponent();
			this->Text = overrideCaption;			
			this->lblDialog->Text = overrideLabel;
			m_retTextBox = tb;
			m_retButton = btn;
			dir_table = gcnew System::Collections::Hashtable(200);
		}

		void setDatabases(vector<std::string>&);
		void dlgDatabaseList::FillTree(vector<std::string>&);
	
		System::Collections::Hashtable^ dir_table;
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~dlgDatabaseList()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TreeView^  tvDbList;
	protected: 
	private: System::Windows::Forms::TextBox^  txtDatabase;


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
			this->tvDbList = (gcnew System::Windows::Forms::TreeView());
			this->txtDatabase = (gcnew System::Windows::Forms::TextBox());
			this->lblDialog = (gcnew System::Windows::Forms::Label());
			this->btnOk = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// tvDbList
			// 
			this->tvDbList->Location = System::Drawing::Point(13, 30);
			this->tvDbList->Name = L"tvDbList";
			this->tvDbList->Size = System::Drawing::Size(306, 156);
			this->tvDbList->TabIndex = 0;
			this->tvDbList->DoubleClick += gcnew System::EventHandler(this, &dlgDatabaseList::tvDbList_DoubleClick);
			this->tvDbList->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &dlgDatabaseList::tvDbList_AfterSelect);
			// 
			// txtDatabase
			// 
			this->txtDatabase->Enabled = false;
			this->txtDatabase->Location = System::Drawing::Point(13, 192);
			this->txtDatabase->Name = L"txtDatabase";
			this->txtDatabase->Size = System::Drawing::Size(306, 20);
			this->txtDatabase->TabIndex = 1;
			// 
			// lblDialog
			// 
			this->lblDialog->AutoSize = true;
			this->lblDialog->Location = System::Drawing::Point(10, 9);
			this->lblDialog->Name = L"lblDialog";
			this->lblDialog->Size = System::Drawing::Size(183, 13);
			this->lblDialog->TabIndex = 3;
			this->lblDialog->Text = L"Select a database from the list below:";
			// 
			// btnOk
			// 
			this->btnOk->Location = System::Drawing::Point(325, 190);
			this->btnOk->Name = L"btnOk";
			this->btnOk->Size = System::Drawing::Size(45, 23);
			this->btnOk->TabIndex = 4;
			this->btnOk->Text = L"OK";
			this->btnOk->UseVisualStyleBackColor = true;
			this->btnOk->Click += gcnew System::EventHandler(this, &dlgDatabaseList::btnOk_Click);
			// 
			// dlgDatabaseList
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(372, 217);
			this->Controls->Add(this->btnOk);
			this->Controls->Add(this->lblDialog);
			this->Controls->Add(this->txtDatabase);
			this->Controls->Add(this->tvDbList);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"dlgDatabaseList";
			this->Text = L"dlgDatabaseList";
			this->Load += gcnew System::EventHandler(this, &dlgDatabaseList::dlgDatabaseList_Load);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &dlgDatabaseList::dlgDatabaseList_FormClosed);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void dlgDatabaseList_Load(System::Object^  sender, System::EventArgs^  e) {				 
		}

	private: System::Void dlgDatabaseList_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
		this->m_retButton->Enabled = true;
	}

	private: System::Void tvDbList_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
		TreeView^ tv = safe_cast<TreeView^>(sender);
		TreeNode^ t = tv->SelectedNode;
		if (t->Text->Contains(".")) {
			this->btnOk->PerformClick();
		}
    }

	private: System::Void tvDbList_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
			 TreeView^ tv = safe_cast<TreeView^>(sender);
			 TreeNode^ t = tv->SelectedNode;
			 if (t->FullPath->Contains(".")) {
				this->txtDatabase->Text = t->FullPath;
			 }
		 }

	private: System::Void btnOk_Click(System::Object^  sender, System::EventArgs^  e) {
		if (!(String::IsNullOrEmpty(this->txtDatabase->Text)) && this->txtDatabase->Text->Length > 0) {
				this->m_retTextBox->Text = this->txtDatabase->Text;				  
		}
		this->Close();
	}

};
}
