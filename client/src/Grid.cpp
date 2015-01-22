#include "Grid.hpp"

void Grid::draw(wxDC& dc, int w, int h)
{
  dc.SetPen(wxPen(wxColor(0, 0, 0), 1));

  int block_height = h / height;
  int block_width = w / width;

  for (int x = 0; x < width; x++)
  {
    for (int y = 0; y < height; y++)
    {
      Point p = at(x, y);
      dc.SetBrush(wxColor(p.x(), p.y(), p.z()));
      dc.DrawRectangle(
        x * block_width, y * block_height, block_width - 1, block_height - 1);
    }
  }
}
