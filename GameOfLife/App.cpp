#include "App.h"
#include "MainWindow.h"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
	MainWindow* mainWindow = new MainWindow(wxT("Game of Life"));
	mainWindow->Show(true);
	return true;
}

