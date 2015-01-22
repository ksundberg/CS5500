#ifndef _DRAWPANE_H_
#define _DRAWPANE_H_

#include "wxwidget.h"
#include "Grid.hpp"

class GridPane : public wxPanel
{

public:
  GridPane(wxFrame* parent);

  void PaintEvent(wxPaintEvent& evt);
  void paintNow();

  void Render(wxDC& dc);

  Grid* grid;

  DECLARE_EVENT_TABLE()
};

#endif //_DRAWPANE_H_
