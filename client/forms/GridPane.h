#ifndef _GRIDPANE_H_
#define _GRIDPANE_H_

#include "wxwidget.h"
#include "Grid.hpp"

#include <memory>

class GridPane : public wxPanel
{

public:
  GridPane(wxFrame* parent);

  void PaintEvent(wxPaintEvent& evt);
  void paintNow();

  void Render(wxDC& dc);

  std::shared_ptr<Grid> grid;

  DECLARE_EVENT_TABLE()
};

#endif //_GRIDPANE_H_
