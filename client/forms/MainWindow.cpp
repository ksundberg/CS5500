#include "MainWindow.h"
#include "logger.h"

enum
{
  ID_Help = 1
};

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame) EVT_MENU(ID_Help, MainWindow::OnHelp)
  EVT_MENU(wxID_EXIT, MainWindow::OnExit)
  EVT_MENU(wxID_ABOUT, MainWindow::OnAbout) wxEND_EVENT_TABLE()

  MainWindow::MainWindow(const wxString& title,
                         const wxPoint& pos,
                         const wxSize& size)
  : wxFrame(NULL, wxID_ANY, title, pos, size)
{
  LOG(DEBUG) << "Creating main window";
  wxMenu* menuFile = new wxMenu;
  menuFile->Append(ID_Help,
                   "&Help...\tCtrl-H",
                   "Help string shown in status bar for this menu item");
  menuFile->AppendSeparator();
  menuFile->Append(wxID_EXIT);
  wxMenu* menuHelp = new wxMenu;
  menuHelp->Append(wxID_ABOUT);
  wxMenuBar* menuBar = new wxMenuBar;
  menuBar->Append(menuFile, "&File");
  menuBar->Append(menuHelp, "&Help");
  SetMenuBar(menuBar);
  CreateStatusBar();
  SetStatusText("Welcome to Torus World!");
}

void MainWindow::OnExit(wxCommandEvent&)
{
  Close(true);
}

void MainWindow::OnAbout(wxCommandEvent&)
{
  LOG(DEBUG) << "About dialog prompt";
  wxMessageBox("This is an awesome project with a torus world",
               "About Torus World",
               wxOK | wxICON_INFORMATION);
}

void MainWindow::OnHelp(wxCommandEvent&)
{
  LOG(DEBUG) << "Help message";
}
