#include "GridPane.h"
#include "logger.h"
#include "PerlinNoise.h"

#include <algorithm>

BEGIN_EVENT_TABLE(GridPane, wxPanel)
EVT_PAINT(GridPane::PaintEvent)
END_EVENT_TABLE()

const double COLOR_MAX = 255;
const int GRID_TILES = 50;

GridPane::GridPane(wxFrame* parent)
  : wxPanel(parent), grid(std::make_shared<Grid>(GRID_TILES, GRID_TILES))
{
  PerlinNoise p;

  std::shared_ptr<matrix2d> noiseMap =
    p.createMatrix2D(grid->width, grid->height, 5);
  for (double x = 0; x < grid->width; x++)
  {
    for (double y = 0; y < grid->height; y++)
    {
      double p = (*noiseMap)[x][y];
      double c = std::min(COLOR_MAX, p * 255);
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
