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
	/// Summary for dlgServerList
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class dlgServerList : public System::Windows::Forms::Form
	{
	private: 
		TextBox^ m_retTextBox;
	private: System::Windows::Forms::Label^  lblDialog;

			 Button^ m_retButton;
	public:	
		dlgServerList(TextBox^ tb, Button^ btn)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//			
			m_retTextBox = tb;	
			m_retButton = btn;
		}
		dlgServerList(TextBox^ tb, Button^ btn, String^ overrideCaption, String^ overrideLabel) {
			InitializeComponent();
			this->Text = overrideCaption;			
			this->lblDialog->Text = overrideLabel;
			m_retTextBox = tb;
			m_retButton = btn;
		}
		void setServers(vector<std::string>&);
	
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~dlgServerList()
		{
			if (components)
			{
				delete components;
			}
		}

	
		
	private: System::Windows::Forms::ComboBox^  cbxServerList;
	private: System::Windows::Forms::Button^  btnOk;
	protected: 

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
			this->cbxServerList = (gcnew System::Windows::Forms::ComboBox());
			this->btnOk = (gcnew System::Windows::Forms::Button());
			this->lblDialog = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// cbxServerList
			// 
			this->cbxServerList->FormattingEnabled = true;
			this->cbxServerList->Location = System::Drawing::Point(7, 43);
			this->cbxServerList->Name = L"cbxServerList";
			this->cbxServerList->Size = System::Drawing::Size(216, 21);
			this->cbxServerList->TabIndex = 0;
			// 
			// btnOk
			// 
			this->btnOk->Location = System::Drawing::Point(229, 41);
			this->btnOk->Name = L"btnOk";
			this->btnOk->Size = System::Drawing::Size(45, 23);
			this->btnOk->TabIndex = 1;
			this->btnOk->Text = L"OK";
			this->btnOk->UseVisualStyleBackColor = true;
			this->btnOk->Click += gcnew System::EventHandler(this, &dlgServerList::btnOk_Click);
			// 
			// lblDialog
			// 
			this->lblDialog->AutoSize = true;
			this->lblDialog->Location = System::Drawing::Point(4, 9);
			this->lblDialog->Name = L"lblDialog";
			this->lblDialog->Size = System::Drawing::Size(168, 13);
			this->lblDialog->TabIndex = 2;
			this->lblDialog->Text = L"Select a server from the list below:";
			// 
			// dlgServerList
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 86);
			this->Controls->Add(this->lblDialog);
			this->Controls->Add(this->btnOk);
			this->Controls->Add(this->cbxServerList);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"dlgServerList";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Select a Server:";
			this->Load += gcnew System::EventHandler(this, &dlgServerList::dlgServerList_Load);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &dlgServerList::dlgServerList_FormClosed);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void dlgServerList_Load(System::Object^  sender, System::EventArgs^  e) {
				 this->cbxServerList->SelectedItem = this->m_retTextBox->Text;
			 }

	private: System::Void btnOk_Click(System::Object^  sender, System::EventArgs^  e) {		
				 
				 if (!(String::IsNullOrEmpty(safe_cast<String ^>(this->cbxServerList->SelectedItem))) && this->cbxServerList->SelectedItem->ToString()->Length > 0) {
					  this->m_retTextBox->Text = this->cbxServerList->SelectedItem->ToString();					  
				  }
				 this->Close();
			 }
	private: System::Void dlgServerList_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
				this->m_retButton->Enabled = true;
			 }
};
}
