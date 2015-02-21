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
  void OnKeyDown(wxKeyEvent& event);

  void Render(wxDC& dc);

  std::vector<std::shared_ptr<Grid>> layers;

  DECLARE_EVENT_TABLE()

private:
      int currentLayer;
      int layerCount;
};

#endif //_GRIDPANE_H_
