#pragma once

#include "NoteClassTable.h"
#include "ScanResult.h"

/*
	ScanIterator - this is a collection iterator class. It manages three types of information.
	1 - current scan process
		*CurrentDatabase
		*CurrentDatabaseTitle
		*CurrentNoteHandle
	2 - SearchQuery: intial search query responsible for our comparisons. 
		We trap info that we are scanning in here. Do a comparison. If it is no match, this item
		is flushed. If there is a match, we persist the item in the SearchResults.

	3 - SearchResults is a (growing) list of match results. 
		This collection is dumped to the output file and flushed following each database scan.
*/

namespace NSFScan 
{
ref class ScanIterator
{
public:	
	ScanIterator(void);
	~ScanIterator(void);

	String^ GetDesignType(WORD);

	NoteClassTable^ note_class_table;
	HANDLE hdb;
	int MatchCount;
	int ScanCount;	
	int ScanTotal;
	
	// current scan info	
	String^ CurrentDatabase;  // db we are on
	String^ CurrentDatabaseTitle;
	NOTEHANDLE	CurrentNoteHandle;
	System::Collections::Generic::List<String^>^ Search_Tokens;   // search tokens
	System::Collections::Generic::List<String^>^ Search_Databases;
	bool IsMatch;			  // tracks if we have at least 1 hit.
	bool ExactMatchesOnly;	  // find only exact matches	
	ScanResult^ SearchQuery;
	System::Collections::Hashtable^ SearchResults;
	void AddSearchResult(ScanResult^);	
};
}
