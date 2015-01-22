#include "wxwidget.h"
#include "MainWindow.h"
#include "GridPane.h"

#include "logger.h"
#include "sample.h"

class DwFort : public wxApp
{
  MainWindow* frame;
  GridPane* gridPane;

public:
  virtual bool OnInit();
};

bool DwFort::OnInit()
{
  init_log(argc, argv);
  LOG(INFO) << hello();

  frame = new MainWindow("Hello World", wxPoint(50, 50), wxSize(200, 200));

  wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

  gridPane = new GridPane((wxFrame*)frame);
  sizer->Add(gridPane, 1, wxEXPAND);

  frame->SetSizer(sizer);
  frame->SetAutoLayout(true);

  frame->Show();
  return true;
}

wxIMPLEMENT_APP(DwFort);
