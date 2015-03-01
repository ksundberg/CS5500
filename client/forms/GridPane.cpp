#include "GridPane.h"
#include "logger.h"

#include <wx/event.h>
#include <algorithm>

enum
{
  BTN_GOLD,
  BTN_LUMBER,
  BTN_NORMAL
};

BEGIN_EVENT_TABLE(GridPane, wxPanel)
EVT_PAINT(GridPane::PaintEvent)
EVT_KEY_DOWN(GridPane::OnKeyDown)
EVT_BUTTON(BTN_GOLD, GridPane::showGoldDensity)
EVT_BUTTON(BTN_LUMBER, GridPane::showLumberDensity)
EVT_BUTTON(BTN_NORMAL, GridPane::showNormal)
END_EVENT_TABLE()

const int GRID_TILES = 50;

GridPane::GridPane(wxFrame* parent)
  : wxPanel(parent), currentLayer(0), filter(Filter::SHOW_NORMAL)
{
  this->World = std::make_shared<Grid>(GRID_TILES, GRID_TILES, GRID_TILES);
  this->World->generateTerrain();

  filterGoldBtn = std::make_shared<wxButton>(
    this, BTN_GOLD, _T("Gold"), wxPoint(10, 10), wxDefaultSize, 0);
  filterLumberBtn = std::make_shared<wxButton>(
    this, BTN_LUMBER, _T("Lumber"), wxPoint(100, 10), wxDefaultSize, 0);
  normalFilterBtn = std::make_shared<wxButton>(
    this, BTN_NORMAL, _T("Normal"), wxPoint(190, 10), wxDefaultSize, 0);
}

void GridPane::PaintEvent(wxPaintEvent&)
{
  wxClientDC dc(this);
  Render(dc);
}

void GridPane::Render(wxDC& dc)
{
  auto size = this->GetSize();
  switch (filter)
  {
  case Filter::SHOW_NORMAL:
    this->World->draw(dc, size.GetWidth(), size.GetHeight(), currentLayer);
    break;
  case Filter::SHOW_GOLD:
    this->World->drawDensityMap(
      dc, size.GetWidth(), size.GetHeight(), 0.2, 0.3);
    break;
  case Filter::SHOW_LUMBER:
    this->World->drawDensityMap(
      dc, size.GetWidth(), size.GetHeight(), 0.6, 0.8);
    break;
  }
}

void GridPane::showGoldDensity(wxCommandEvent&)
{
  LOG(DEBUG) << "GridPane::" << __FUNCTION__;
  filter = Filter::SHOW_GOLD;
  GetParent()->Refresh();
}

void GridPane::showNormal(wxCommandEvent&)
{
  LOG(DEBUG) << "GridPane::" << __FUNCTION__;
  filter = Filter::SHOW_NORMAL;
  GetParent()->Refresh();
}
void GridPane::showLumberDensity(wxCommandEvent&)
{
  LOG(DEBUG) << "GridPane::" << __FUNCTION__;
  filter = Filter::SHOW_LUMBER;
  GetParent()->Refresh();
}

void GridPane::OnKeyDown(wxKeyEvent& event)
{
  LOG(DEBUG) << "GridPane::" << __FUNCTION__;

  switch (event.GetKeyCode())
  {
  case WXK_UP:
    currentLayer++;
    if (currentLayer >= GRID_TILES) currentLayer = 0;
    break;

  case WXK_DOWN:
    currentLayer--;
    if (currentLayer < 0) currentLayer = GRID_TILES - 1;
    break;

  default:
    event.Skip();
    return;
  }
  GetParent()->Refresh();
}
