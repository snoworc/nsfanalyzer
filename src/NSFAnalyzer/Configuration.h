#pragma once

using namespace System;
using namespace System::Xml;
using namespace System::IO;
using namespace System::Windows::Forms;


namespace NSFAnalyzer {

	public ref class ConfigurationTool
	{
		private:
			String^ m_fileFormat;
			String^ m_filePath;
			String^ m_server;
			String^ m_database;
			bool m_isIncludeChecked;
			bool m_isExcludeChecked;
			bool m_isIncludeRecurseChecked;
			bool m_isExcludeRecurseChecked;
			bool m_isDesignOnly;
			bool m_isExactMatch;
			bool m_isAutoLaunching;
			
			// ... TODO: use std::vector objects for the last member vars, 
			// in order to keep a clean separation from the business object and the presentation layer.
			ListBox^ m_IncludeFolders;
			ListBox^ m_ExcludeFolders;
			ListBox^ m_SearchKeys;
			ListBox^ m_StatusField;
			
		public:	
			ConfigurationTool(void);
			bool Read(String^);
			void Write(String^);

			String^ GetFileFormat() { return m_fileFormat; }
			void SetFileFormat(String^ inputValue){ m_fileFormat = inputValue; }

			String^ GetFilePath() { return m_filePath; }
			void SetFilePath(String^ inputValue){ m_filePath = inputValue; }

			String^ GetServer(){ return m_server; }
			void SetServer(String^ inputValue){ m_server = inputValue; }

			String^ GetDatabase(){ return m_database; }
			void SetDatabase(String^ inputValue){ m_database = inputValue; }

			bool GetIncludeFlag() { return m_isIncludeChecked; }
			void SetIncludeFlag(bool inputValue){ m_isIncludeChecked = inputValue; }

			bool GetExcludeFlag(){ return m_isExcludeChecked; }
			void SetExcludeFlag(bool inputValue){ m_isExcludeChecked = inputValue; }

			bool GetIncludeRecurseFlag(){ return m_isIncludeRecurseChecked; }
			void SetIncludeRecurseFlag(bool inputValue){ m_isIncludeRecurseChecked = inputValue; }

			bool GetExcludeRecurseFlag(){ return m_isExcludeRecurseChecked; }
			void SetExcludeRecurseFlag(bool inputValue){ m_isExcludeRecurseChecked = inputValue; }

			bool GetIsDesignOnly(){ return m_isDesignOnly; }
			void SetIsDesignOnly(bool inputValue){ m_isDesignOnly = inputValue; }

			property bool IsAutoLaunching {
				bool get() { return m_isAutoLaunching; }
				void set(bool chk) { m_isAutoLaunching = chk; }
			}
			
			bool GetIsExactMatch(){ return m_isExactMatch; }
			void SetIsExactMatch(bool inputValue){ m_isExactMatch = inputValue; }

			// TODO: clean this up
			ListBox^ GetIncludeFolders(){ return m_IncludeFolders; }
			void SetIncludeFolders(ListBox^ inputValue){ m_IncludeFolders = inputValue; }

			ListBox^ GetExcludeFolders(){ return m_ExcludeFolders; }
			void SetExcludeFolders(ListBox^ inputValue){ m_ExcludeFolders = inputValue; }

			ListBox^ GetSearchKeys(){ return m_SearchKeys; }
			void SetSearchKeys(ListBox^ inputValue){ m_SearchKeys = inputValue; }

			void UpdateStatusField(String^ inputValue){ m_StatusField->Items->Insert(0, inputValue); }
			void SetStatusField(ListBox^ inputValue){ m_StatusField = inputValue; }
	};
}