#include "StdAfx.h"
#include "NoteClass.h"

NoteClass::NoteClass(WORD note_class_id, String^ note_class_desc, DWORD note_scan_count){
	this->fNoteClass = note_class_id;
	this->sNoteClass = note_class_desc;
	this->dwScanCount = note_scan_count;
}
