#include "StdAfx.h"
#include "NoteClassTable.h"

NoteClassTable::NoteClassTable() {	
	this->Table = gcnew System::Collections::Generic::List<NoteClass^>();
	this->Table->Add(gcnew NoteClass(NOTE_CLASS_DOCUMENT, "Document", 0));
	this->Table->Add(gcnew NoteClass(NOTE_CLASS_INFO, "Help-About", 0));
	this->Table->Add(gcnew NoteClass(NOTE_CLASS_FORM, "Form", 0));
	this->Table->Add(gcnew NoteClass(NOTE_CLASS_VIEW, "View", 0));
	this->Table->Add(gcnew NoteClass(NOTE_CLASS_ICON, "Icon", 0));
	this->Table->Add(gcnew NoteClass(NOTE_CLASS_DESIGN, "Design Collection", 0));
	this->Table->Add(gcnew NoteClass(NOTE_CLASS_ACL, "ACL", 0));
	this->Table->Add(gcnew NoteClass(NOTE_CLASS_HELP_INDEX, "Help index", 0));
	this->Table->Add(gcnew NoteClass(NOTE_CLASS_HELP, "Help-Using", 0));
	this->Table->Add(gcnew NoteClass(NOTE_CLASS_FILTER, "Agent", 0));
	this->Table->Add(gcnew NoteClass(NOTE_CLASS_FIELD, "Shared Field", 0));
	this->Table->Add(gcnew NoteClass(NOTE_CLASS_REPLFORMULA, "Replication Formula", 0));
	this->Table->Add(gcnew NoteClass(NOTE_CLASS_PRIVATE, "Private Note", 0));
	this->NumEntries = this->Table->Count;	
}
NoteClassTable::~NoteClassTable() {
	this->NumEntries = 0;
	delete this->Table;
}
