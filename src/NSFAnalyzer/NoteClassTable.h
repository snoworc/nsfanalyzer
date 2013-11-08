#pragma once

#include "NoteClass.h"

ref class NoteClassTable
{
public:
	NoteClassTable(void);
	~NoteClassTable(void);
	int NumEntries;
	System::Collections::Generic::List<NoteClass^>^ Table;
};

