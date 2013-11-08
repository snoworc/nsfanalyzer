#pragma once

using namespace System::Windows::Forms;

ref class ListboxHandler
{
public:
	ListboxHandler(void);
	void AddItem(ListBox^ lb, TextBox^ tb);
	void RemoveSelectedItem(ListBox^ lb);
};
