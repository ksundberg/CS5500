#include "GridPane.h"
#include "logger.h"

#include <algorithm>

BEGIN_EVENT_TABLE(GridPane, wxPanel)
EVT_PAINT(GridPane::PaintEvent)
END_EVENT_TABLE()

const double COLOR_MAX = 255;
const int GRID_TILES = 20;

GridPane::GridPane(wxFrame* parent)
  : wxPanel(parent), grid(new Grid(GRID_TILES, GRID_TILES))
{
  for (double x = 0; x < grid->width; x++)
  {
    for (double y = 0; y < grid->height; y++)
    {
      double c = std::min(COLOR_MAX, x * y);
      grid->set(x, y, {c, c, c});
    }
  }
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
  auto size = this->GetSize();
  grid->draw(dc, size.GetWidth(), size.GetHeight());
}
