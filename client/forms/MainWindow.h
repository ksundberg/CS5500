#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include "wxwidget.h"

class MainWindow: public wxFrame
{
  public:
    MainWindow(const wxString& title, const wxPoint& pos, const wxSize& size);
  private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};

enum
{
  ID_Hello = 1
};

#endif //_MAINWINDOW_H_
