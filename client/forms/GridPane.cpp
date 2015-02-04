#include "GridPane.h"
#include "logger.h"

#include <algorithm>

BEGIN_EVENT_TABLE(GridPane, wxPanel)
EVT_PAINT(GridPane::PaintEvent)
END_EVENT_TABLE()

const int GRID_TILES = 50;

GridPane::GridPane(wxFrame* parent)
  : wxPanel(parent), grid(std::make_shared<Grid>(GRID_TILES, GRID_TILES))
{
  grid->generateTerrain();
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
