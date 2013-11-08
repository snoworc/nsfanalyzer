#include "StdAfx.h"
#include "ScanIterator.h"

using namespace NSFScan;

ScanIterator::ScanIterator(void)
{
	this->SearchQuery = gcnew ScanResult();
	this->IsMatch = false;
	this->ScanCount = 0;
	this->ScanTotal = 0;
	this->MatchCount = 0;
	this->CurrentDatabase = String::Empty;	
	this->note_class_table = gcnew NoteClassTable();
	this->Search_Tokens = gcnew System::Collections::Generic::List<String^>(10);
	this->Search_Databases = gcnew System::Collections::Generic::List<String^>(500);
	this->SearchResults = gcnew System::Collections::Hashtable(100);
}

ScanIterator::~ScanIterator(void)
{
}
String^ ScanIterator::GetDesignType(WORD flag) {	
	for (int i=0;i<this->note_class_table->NumEntries;i++) {
		if ((WORD)flag & this->note_class_table->Table[i]->fNoteClass) {
			return this->note_class_table->Table[i]->sNoteClass;
		}
	}
	return "Unrecognized Class";
}

void ScanIterator::AddSearchResult(ScanResult^ item) {	
	ScanResult^ item_copy = item;
	item_copy->Occurrences = (unsigned int)1;
	ScanResult^ item_existing;

	String^ key = item->GetKey();
	if (this->SearchResults->Count == 0) {
		this->SearchResults->Add(key, safe_cast<ScanResult^>(item_copy));
	} else {
		if (this->SearchResults->ContainsKey(key)) {			
			System::Collections::IDictionaryEnumerator^ e = this->SearchResults->GetEnumerator();
			while (e->MoveNext()) {
				if (e->Key->Equals(key)) {
					item_existing = safe_cast<ScanResult^>(e->Entry.Value);					
					item_copy->Occurrences += item_existing->Occurrences;
					this->SearchResults->Remove(key);
					this->SearchResults->Add(key, item_copy);
					break;
				}
			}
		} else {
			this->SearchResults->Add(key, safe_cast<ScanResult^>(item_copy));
		}
	}


}
