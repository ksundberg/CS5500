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

  void showGoldDensity(wxCommandEvent& event);
  void showLumberDensity(wxCommandEvent& event);

  void Render(wxDC& dc);



  std::shared_ptr<Grid> World;

  wxButton *materialDenisityGoldButton;
  wxButton *materialDenisityLumberButton;
  //wxButton *material2DenisityMap

  DECLARE_EVENT_TABLE()

private:
      int currentLayer;
};

#endif //_GRIDPANE_H_
