#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include "wxwidget.h"

class MainWindow : public wxFrame
{
public:
  MainWindow(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
  void OnHelp(wxCommandEvent& event);
  void OnExit(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);
  void OnInventory(wxCommandEvent& event);
  void OnDungeonTest(wxCommandEvent& event);
  wxDECLARE_EVENT_TABLE();
};

#endif //_MAINWINDOW_H_
