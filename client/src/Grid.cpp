#include "Grid.hpp"

void Grid::draw(wxDC& dc)
{
  dc.SetPen(wxPen(wxColor(0, 0, 0), 1));

  for (int x = 0; x < width; x++)
  {
    for (int y = 0; y < height; y++)
    {
      double c = at(x, y);
      dc.SetBrush(wxColour(c, c, c));
      dc.DrawRectangle(x * 20, y * 20, 19, 19);
    }
  }
}
