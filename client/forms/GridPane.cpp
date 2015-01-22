#include "GridPane.h"

#include "logger.h"

#include <algorithm>

BEGIN_EVENT_TABLE(GridPane, wxPanel)
EVT_PAINT(GridPane::PaintEvent)
END_EVENT_TABLE()

GridPane::GridPane(wxFrame* parent) : wxPanel(parent), grid(new Grid(20, 20))
{
  for (int x = 0; x < 20; x++)
    for (int y = 0; y < 20; y++)
      grid->set(x, y, std::min(255, x * y));
}

void GridPane::PaintEvent(wxPaintEvent&)
{
  wxPaintDC dc(this);
  Render(dc);
}

void GridPane::paintNow()
{
  wxClientDC dc(this);
  Render(dc);
}

void GridPane::Render(wxDC& dc)
{
  grid->draw(dc);
}
