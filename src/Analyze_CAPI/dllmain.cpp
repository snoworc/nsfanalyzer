// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <lapiplat.h>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
		// called when DLL is first mapped into calling process's address space
		case DLL_PROCESS_ATTACH:
		// Initialize the C API.
		NotesInitExtended((int)0, (char**)NULL); // not using command line args
		break;

		// called when DLL is un-mapped from calling process's address space
		case DLL_PROCESS_DETACH:
		// Terminate the API.
		NotesTerm();
		break;

	}
	return TRUE;
}
