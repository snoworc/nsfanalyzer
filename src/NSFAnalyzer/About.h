#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace NSFAnalyzer {

	/// <summary>
	/// Summary for About
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class About : public System::Windows::Forms::Form
	{
	public:
		About(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~About()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  lblAbout;
	private: System::Windows::Forms::LinkLabel^  lnkEmail;

	private: System::Windows::Forms::Label^  lblTbn;
	private: System::Windows::Forms::Label^  lblStatic;
	private: System::Windows::Forms::TextBox^  txtEmail;
	private: System::Windows::Forms::LinkLabel^  lnkWebsite;

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
			this->lblAbout = (gcnew System::Windows::Forms::Label());
			this->lnkEmail = (gcnew System::Windows::Forms::LinkLabel());
			this->lblTbn = (gcnew System::Windows::Forms::Label());
			this->lblStatic = (gcnew System::Windows::Forms::Label());
			this->txtEmail = (gcnew System::Windows::Forms::TextBox());
			this->lnkWebsite = (gcnew System::Windows::Forms::LinkLabel());
			this->SuspendLayout();
			// 
			// lblAbout
			// 
			this->lblAbout->AutoSize = true;
			this->lblAbout->Location = System::Drawing::Point(12, 43);
			this->lblAbout->Name = L"lblAbout";
			this->lblAbout->Size = System::Drawing::Size(135, 13);
			this->lblAbout->TabIndex = 0;
			this->lblAbout->Text = L"NSF Analyzer version 1.0.3";
			// 
			// lnkEmail
			// 
			this->lnkEmail->AutoSize = true;
			this->lnkEmail->LinkArea = System::Windows::Forms::LinkArea(11, 16);
			this->lnkEmail->Location = System::Drawing::Point(13, 73);
			this->lnkEmail->Name = L"lnkEmail";
			this->lnkEmail->Size = System::Drawing::Size(148, 17);
			this->lnkEmail->TabIndex = 1;
			this->lnkEmail->TabStop = true;
			this->lnkEmail->Text = L"Created by T. Brian Nichols\r\n";
			this->lnkEmail->UseCompatibleTextRendering = true;
			this->lnkEmail->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &About::lnkEmail_LinkClicked);
			// 
			// lblTbn
			// 
			this->lblTbn->AutoSize = true;
			this->lblTbn->Font = (gcnew System::Drawing::Font(L"Constantia", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblTbn->Location = System::Drawing::Point(12, 9);
			this->lblTbn->Name = L"lblTbn";
			this->lblTbn->Size = System::Drawing::Size(156, 18);
			this->lblTbn->TabIndex = 2;
			this->lblTbn->Text = L"TBN Consulting, Inc.";
			// 
			// lblStatic
			// 
			this->lblStatic->AutoSize = true;
			this->lblStatic->Location = System::Drawing::Point(12, 102);
			this->lblStatic->Name = L"lblStatic";
			this->lblStatic->Size = System::Drawing::Size(34, 13);
			this->lblStatic->TabIndex = 3;
			this->lblStatic->Text = L"email:";
			// 
			// txtEmail
			// 
			this->txtEmail->BackColor = System::Drawing::SystemColors::Control;
			this->txtEmail->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->txtEmail->Location = System::Drawing::Point(53, 102);
			this->txtEmail->Name = L"txtEmail";
			this->txtEmail->ReadOnly = true;
			this->txtEmail->Size = System::Drawing::Size(158, 13);
			this->txtEmail->TabIndex = 4;
			this->txtEmail->Text = L"timothy_b_nichols@yahoo.com";
			// 
			// lnkWebsite
			// 
			this->lnkWebsite->AutoSize = true;
			this->lnkWebsite->LinkArea = System::Windows::Forms::LinkArea(9, 28);
			this->lnkWebsite->Location = System::Drawing::Point(11, 129);
			this->lnkWebsite->Name = L"lnkWebsite";
			this->lnkWebsite->Size = System::Drawing::Size(204, 17);
			this->lnkWebsite->TabIndex = 5;
			this->lnkWebsite->TabStop = true;
			this->lnkWebsite->Text = L"website: http://www.codedementia.com/";
			this->lnkWebsite->UseCompatibleTextRendering = true;
			this->lnkWebsite->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &About::lnkWebsite_LinkClicked);
			// 
			// About
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(227, 155);
			this->Controls->Add(this->lnkWebsite);
			this->Controls->Add(this->txtEmail);
			this->Controls->Add(this->lblStatic);
			this->Controls->Add(this->lblTbn);
			this->Controls->Add(this->lnkEmail);
			this->Controls->Add(this->lblAbout);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"About";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->Text = L"NSFAnalyzer";
			this->Load += gcnew System::EventHandler(this, &About::About_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void About_Load(System::Object^  sender, System::EventArgs^  e) {				 
				 String ^ version = System::Reflection::Assembly::GetExecutingAssembly()->GetName()->Version->ToString();
				 this->lblAbout->Text = "NSFAnalyzer version " + version;
			 }
	private: System::Void lnkEmail_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {
				 try {
					System::Diagnostics::Process::Start("mailto://timothy_b_nichols@yahoo.com");
				 } catch (Exception^) {
					 try {
						 System::Diagnostics::ProcessStartInfo^ pi = gcnew System::Diagnostics::ProcessStartInfo();
						 pi->FileName = "iexplore.exe";
						 pi->WindowStyle = System::Diagnostics::ProcessWindowStyle::Normal;
						 pi->Arguments = "mailto://timothy_b_nichols@yahoo.com";
						 pi->UseShellExecute = true;
						 System::Diagnostics::Process::Start(pi);
					 } catch(Exception ^ex) {
						MessageBox::Show(ex->Message + "\n\n" + ex->StackTrace, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
					 }
				 }
			 }

private: System::Void lnkWebsite_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {
				try {
					System::Diagnostics::Process::Start("http://www.codedementia.com/");
				 } catch (Exception^) {
					 try {
						 System::Diagnostics::ProcessStartInfo^ pi = gcnew System::Diagnostics::ProcessStartInfo();
						 pi->FileName = "iexplore.exe";
						 pi->WindowStyle = System::Diagnostics::ProcessWindowStyle::Normal;
						 pi->Arguments = "http://www.codedementia.com/";
						 pi->UseShellExecute = true;
						 System::Diagnostics::Process::Start(pi);
					 } catch(Exception ^ex) {
						MessageBox::Show(ex->Message + "\n\n" + ex->StackTrace, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
					 }
				 }
		 }
};
}
