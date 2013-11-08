#pragma once

using namespace System;

#include <lapiplat.h>
#include <osenv.h>
#include <ns.h>
#include <osmem.h>
#include <nsfsearc.h>
#include <osfile.h>
#include <nsfdb.h>
#include <osfile.h>
#include <names.h>
#include <nsferr.h>
#include <textlist.h>
#include <ods.h>
#include <odstypes.h>
#include <oleods.h>
#include <rsrcods.h>
#include <fsods.h>
#include <actods.h>
#include <actprop.h>
#include <nsfnote.h>
#include <kfm.h>
#include <dname.h>
#include <colorods.h>
#include <global.h>
#include <intl.h>
#include <nsf.h>
#include <nsfobjec.h>
#include <misc.h>
#include <osmem.h>
#include <osmisc.h>
#include <ostime.h>
#include <stdnames.h>
#include <editods.h>
#include <odserr.h>
#include <queryods.h>

/*
	NoteClass is a helper function that can populate a table of meaningful descriptions, given
	a hexidecimal design class mask.
*/
ref class NoteClass 
{
	public:
		NoteClass(WORD, String^, DWORD);

		WORD fNoteClass;			/* NOTE_CLASS value */
		String^ sNoteClass;			/* descriptive string */

		/* reservered for future use: */
		DWORD dwScanCount;			/* how many of that class was scanned */
};
