#include <vector>
#include "MainWindow.h"
#include "logger.h"
#include "canvas.h"
#include "itemgen.h"
#include "dungeon.h"

enum
{
  ID_Help = 1,
  ID_Inventory,
  ID_Dungeon
};

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame) EVT_MENU(ID_Help, MainWindow::OnHelp)
  EVT_MENU(wxID_EXIT, MainWindow::OnExit)
  EVT_MENU(wxID_ABOUT, MainWindow::OnAbout)
  EVT_MENU(ID_Inventory, MainWindow::OnInventory)
  EVT_MENU(ID_Dungeon, MainWindow::OnDungeonTest) wxEND_EVENT_TABLE()

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

  wxMenu* menuTools = new wxMenu;
  menuTools->Append(ID_Inventory, "&Inventory...\tCtrl-I");
  menuTools->Append(ID_Dungeon, "&Dungeon...\tCtrl-d");

  wxMenuBar* menuBar = new wxMenuBar;
  menuBar->Append(menuFile, "&File");
  menuBar->Append(menuHelp, "&Help");
  menuBar->Append(menuTools, "&Tools");
  SetMenuBar(menuBar);
  CreateStatusBar();
  SetStatusText("Welcome to Torus World!");

  new TestGLCanvas(this, NULL);
  SetClientSize(600, 600);
  Show();
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

void MainWindow::OnInventory(wxCommandEvent&)
{
  // Experiment with inventory and items.
  auto items = ItemGen::genItems().getAllItems();
  LOG(DEBUG) << "Inventory:";
  for (auto i : items)
  {
    LOG(DEBUG) << "Name: " << i.getName();
    LOG(DEBUG) << "Count: " << i.getCount();
    LOG(DEBUG) << "Durability " << i.getDurability();
  }
}

void MainWindow::OnDungeonTest(wxCommandEvent&)
{
  ChunkList chunks;
  Dungeon::makeDungeon(chunks);
  Dungeon::printDungeon(chunks);
}
