#include "GridPane.h"
#include "logger.h"

#include <algorithm>

BEGIN_EVENT_TABLE(GridPane, wxPanel)
EVT_PAINT(GridPane::PaintEvent)
EVT_KEY_DOWN(GridPane::OnKeyDown)
EVT_BUTTON(1, GridPane::showGoldDensity)
EVT_BUTTON(2, GridPane::showLumberDensity)
END_EVENT_TABLE()

const int GRID_TILES = 50;

GridPane::GridPane(wxFrame* parent)
  : wxPanel(parent), currentLayer(0)
{
    this->World = std::make_shared<Grid>(GRID_TILES, GRID_TILES, GRID_TILES);
    this->World->generateTerrain();
    
    materialDenisityGoldButton = new wxButton(this, 1, _T("Gold"), wxPoint(10,10), wxDefaultSize, 0);
    materialDenisityLumberButton = new wxButton(this, 2, _T("Lumber"), wxPoint(100,10), wxDefaultSize, 0);
}

void GridPane::PaintEvent(wxPaintEvent&)
{
  wxClientDC dc(this);
  Render(dc);
}

void GridPane::Render(wxDC& dc)
{
  auto size = this->GetSize();
  this->World->draw(dc, size.GetWidth(), size.GetHeight(), currentLayer);
}

void GridPane::showGoldDensity(wxCommandEvent& event){
  std::cout << event.GetInt() << std::endl;
  auto size = this->GetSize();
  wxClientDC dc(this);
  this->World->drawDensityMap(dc, size.GetWidth(), size.GetHeight(), 0.2, 0.3);
}

void GridPane::showLumberDensity(wxCommandEvent& event){
  std::cout << event.GetInt() << std::endl;
  auto size = this->GetSize();
  wxClientDC dc(this);
  this->World->drawDensityMap(dc, size.GetWidth(), size.GetHeight(), 0.6, 0.8);
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
      if (currentLayer >= GRID_TILES)
          currentLayer = 0;
    break;

  case WXK_DOWN:
      currentLayer--;
      if (currentLayer < 0)
          currentLayer = GRID_TILES-1;
    break;

  default:
    event.Skip();
    return;
  }
  GetParent()->Refresh();
}
