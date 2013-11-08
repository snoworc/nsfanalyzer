#include "StdAfx.h"
#include "ListboxHandler.h"

ListboxHandler::ListboxHandler(void)
{
}

void ListboxHandler::AddItem(ListBox^ lb, TextBox^ tb) {
	if (tb->Text->Length > 0) {
		if (!lb->Items->Contains(tb->Text)) {
			lb->Items->Add(tb->Text);
			tb->Clear();
		}
	}
}


void ListboxHandler::RemoveSelectedItem(ListBox^ lb) {
	if (lb->SelectedItems->Count > 0) {
		while (lb->SelectedItems->Count > 0) {
			lb->Items->Remove(lb->SelectedItem);
		}
	}
}