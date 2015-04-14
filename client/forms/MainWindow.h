#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include "wxwidget.h"
#include "graphics.h"
#include "GridPane.h"
#include "world.h"

class MainWindow : public wxFrame
{
public:
  MainWindow(const wxString& title,
             std::shared_ptr<World> world,
             const wxPoint& pos,
             const wxSize& size);

private:
  void OnHelp(wxCommandEvent& event);
  void OnExit(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);
  void OnInventory(wxCommandEvent& event);
  void OnDungeonTest(wxCommandEvent& event);
  void OnDisplayWorld(wxCommandEvent& event);
  void OnDisplayCubes(wxCommandEvent& event);

  DECLARE_EVENT_TABLE();

  std::shared_ptr<wxGLCanvas> gameCanvas;
  GridPane* gridPane;
  wxBoxSizer* sizer;
};

#endif //_MAINWINDOW_H_
