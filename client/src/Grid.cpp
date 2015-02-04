#include "Grid.hpp"

const double COLOR_MAX = 255;

void Grid::generateTerrain()
{
  PerlinNoise perlin;
  std::shared_ptr<matrix2d> noiseMap =
    perlin.createMatrix2D(width, height, 5);

  perlin.smooth(noiseMap);

  for (double x = 0; x < width; x++)
  {
    for (double y = 0; y < height; y++)
    {
      double p = (*noiseMap)[x][y];
      double c = std::min(COLOR_MAX, p * 255);
      set(x, y, {c, c, c});
    }
  }
}

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
