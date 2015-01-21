#include "MainWindow.h"
#include "logger.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
  EVT_MENU(ID_Hello, MainWindow::OnHello)
  EVT_MENU(wxID_EXIT, MainWindow::OnExit)
  EVT_MENU(wxID_ABOUT, MainWindow::OnAbout)
wxEND_EVENT_TABLE()

MainWindow::MainWindow(const wxString& title, const wxPoint& pos, const wxSize& size)
  : wxFrame(NULL, wxID_ANY, title, pos, size)
{
  LOG(DEBUG) << "Making main window frame";
  wxMenu *menuFile = new wxMenu;
  menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
      "Help string shown in status bar for this menu item");
  menuFile->AppendSeparator();
  menuFile->Append(wxID_EXIT);
  wxMenu *menuHelp = new wxMenu;
  menuHelp->Append(wxID_ABOUT);
  wxMenuBar *menuBar = new wxMenuBar;
  menuBar->Append( menuFile, "&File" );
  menuBar->Append( menuHelp, "&Help" );
  SetMenuBar( menuBar );
  CreateStatusBar();
  SetStatusText( "Welcome to dwfort!" );
}

void MainWindow::OnExit(wxCommandEvent& event)
{
  Close( true );
}

void MainWindow::OnAbout(wxCommandEvent& event)
{
  LOG(DEBUG) << "About dialog prompt";
  wxMessageBox( "This is a wxWidgets' Hello world sample",
      "About Hello World", wxOK | wxICON_INFORMATION );
}

void MainWindow::OnHello(wxCommandEvent& event)
{
  LOG(DEBUG) << "Hello world message";
  wxLogMessage("Hello world from wxWidgets!");
}
