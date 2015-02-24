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

  void showGoldDensity(wxCommandEvent&);
  void showLumberDensity(wxCommandEvent&);
  void showNormal(wxCommandEvent&);

  void Render(wxDC& dc);

  std::shared_ptr<Grid> World;

  std::shared_ptr<wxButton> filterGoldBtn;
  std::shared_ptr<wxButton> filterLumberBtn;
  std::shared_ptr<wxButton> normalFilterBtn;

  DECLARE_EVENT_TABLE()

private:
  enum struct Filter
  {
    SHOW_NORMAL,
    SHOW_GOLD,
    SHOW_LUMBER
  };
  int currentLayer;
  Filter filter;
};

#endif //_GRIDPANE_H_
