#include "MainForm.h"
#include "stdio.h"
using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void Main(array<String^>^ args)
{
	FILE *f;
	fopen_s(&f, "changelog.txt", "w");
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	TXT_Viewer::MainForm form;
	Application::Run(%form);
}
