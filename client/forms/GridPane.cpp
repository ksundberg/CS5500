#include "GridPane.h"
#include "logger.h"

#include <algorithm>

BEGIN_EVENT_TABLE(GridPane, wxPanel)
EVT_PAINT(GridPane::PaintEvent)
EVT_KEY_DOWN(GridPane::OnKeyDown)
END_EVENT_TABLE()

const int GRID_TILES = 50;

GridPane::GridPane(wxFrame* parent)
  : wxPanel(parent), currentLayer(0), layerCount(10)
{
    for(int i=0; i < layerCount; i++)
    {
      auto grid = std::make_shared<Grid>(GRID_TILES, GRID_TILES);
      grid->generateTerrain();
      layers.push_back(grid);
    }
}

void GridPane::PaintEvent(wxPaintEvent&)
{
  wxClientDC dc(this);
  Render(dc);
}

void GridPane::Render(wxDC& dc)
{
  auto size = this->GetSize();
  layers[currentLayer]->draw(dc, size.GetWidth(), size.GetHeight());
}

void GridPane::OnKeyDown(wxKeyEvent& event)
{
  LOG(DEBUG) << "GridPane::" << __FUNCTION__;

  wxChar uc = event.GetUnicodeKey();
  if ( uc != WXK_NONE && uc >= 'A' && uc <= 'z')
  {
      LOG(DEBUG) << "You pressed " << uc << " " << (char)uc;
  }

  switch (event.GetKeyCode())
  {
  case WXK_UP:
      currentLayer++;
      if (currentLayer >= layerCount)
          currentLayer = 0;
    break;

  case WXK_DOWN:
      currentLayer--;
      if (currentLayer < 0)
          currentLayer = layerCount-1;
    break;

  default:
    event.Skip();
    return;
  }
  GetParent()->Refresh();
}
