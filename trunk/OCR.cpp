#include "stdafx.h"
#include "FormMainWindow.h"
#include <windows.h>

using namespace OCR;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	System::Threading::Thread::CurrentThread->ApartmentState = System::Threading::ApartmentState::STA;
	Application::Run(new FormMainWindow());
	return 0;
}