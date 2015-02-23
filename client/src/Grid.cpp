#include "Grid.hpp"

const double COLOR_MAX = 255;

void Grid::generateTerrain()
{
  PerlinNoise perlin;
  std::shared_ptr<matrix3d> noiseMap = perlin.createMatrix3D(width, height, depth, 5);

  //perlin.smooth(noiseMap);

  for (double x = 0; x < width; x++)
  {
    for (double y = 0; y < height; y++)
    {
      for (double z = 0; z < height; z++)
      {
        double p = (*noiseMap)[x][y][z];
        double c = std::min(COLOR_MAX, p * 255);
        set(x, y, z, {c, c, c});
      }
    }
  }
}

void Grid::draw(wxDC& dc, int w, int h, int z)
{
  dc.SetPen(wxPen(wxColor(0, 0, 0), 1));

  int block_height = h / height;
  int block_width = w / width;

  for (int x = 0; x < width; x++)
  {
    for (int y = 0; y < height; y++)
    {
      Point p = at(x, y, z);
      dc.SetBrush(wxColor(p.x(), p.y(), p.z()));
      dc.DrawRectangle(
        x * block_width, y * block_height, block_width - 1, block_height - 1);
    }
  }
}
