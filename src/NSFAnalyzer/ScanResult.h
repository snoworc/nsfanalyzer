#pragma once

using namespace System;

namespace NSFScan  {
	ref class ScanResult
	{
	private:

	public:
		ScanResult(void);

		unsigned int NoteID;	  // item we are interrogating
		String^ DatabaseFile;
		String^ DesignClass;	  // type of design object we are interrogating
		String^ DesignTitle;	  // type of note we are looking at
		String^ FieldName;		  // name of item we are interrogating
		String^ DataType;		  // determines how to scan the item		
		String^ Details;
		unsigned int Occurrences;
		int MatchType;			  // if any item on the note is a match
		String^ MatchToken;		  // which token matched	

		String^ GetKey() {
			return this->DatabaseFile + "¥" + NoteID + "¥" + FieldName + "¥" + this->DataType + "¥" + this->Details;
		}

		String^ GetDesignDetails() {
			return GetDesignDetails(true);
		}

		String^ GetDesignDetails(bool useHtml) {
			String^ retTxt = String::Empty;

			if (this->Occurrences > 1) {
				retTxt = this->Details + " (" + this->Occurrences + " occurrences)";
			} else {
				retTxt = this->Details;
			}

			if (retTxt->Equals(String::Empty) && useHtml) retTxt = "&nbsp;";

			return retTxt;
		}
	
	};
}