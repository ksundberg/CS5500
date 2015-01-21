#include "wxwidget.h"
#include "MainWindow.h"

#include "logger.h"
#include "sample.h"

class DwFort: public wxApp
{
  public:
    virtual bool OnInit();
};

bool DwFort::OnInit()
{
  init_log(argc, argv);
  LOG(INFO) << hello();
  MainWindow *frame = new MainWindow( "Hello World", wxPoint(50, 50), wxSize(200, 200) );
  frame->Show( true );
  return true;
}

wxIMPLEMENT_APP(DwFort);
