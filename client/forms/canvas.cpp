// Example application modified from the wxWidgets demo here:
// http://fossies.org/dox/wxWidgets-3.0.2/cube_8cpp_source.html
#include "logger.h"
#include "canvas.h"
#include <glm/gtc/noise.hpp>

// control ids
enum
{
  GameTimer = wxID_HIGHEST + 1
};

BEGIN_EVENT_TABLE(GameLoopCanvas, wxGLCanvas)
EVT_PAINT(GameLoopCanvas::OnPaint) EVT_KEY_DOWN(GameLoopCanvas::OnKeyDown)
  EVT_KEY_UP(GameLoopCanvas::OnKeyUp)
  EVT_TIMER(GameTimer, GameLoopCanvas::OnGameTimer)
  EVT_MOTION(GameLoopCanvas::OnMouseUpdate) END_EVENT_TABLE()

  GameLoopCanvas::GameLoopCanvas(wxWindow* parent, wxSize size, int* attribList)
  : wxGLCanvas(parent,
               wxID_ANY,
               attribList,
               wxDefaultPosition,
               size,
               wxFULL_REPAINT_ON_RESIZE)
  , m_spinTimer(this, GameTimer)
{
  GameInit();
}

GameLoopCanvas::~GameLoopCanvas()
{
  delete chunk_manager;
}

void GameLoopCanvas::GenerateBlocks(ChunkManager* cm)
{
  // Just an example of how to use the ChunkManager
  auto noise2d = [](int x, int y, int amplitude, int height)
  {
    return (height + amplitude * glm::simplex(glm::vec2(x, y)));
  };

  for (int i = 0; i < cm->BOUNDX / 5; i++)
  {
    for (int j = 0; j < cm->BOUNDY / 5; j++)
    {
      BlockType type;
      auto branchOn = rand() % 11;
      if (branchOn < 1)
      {
        type = BlockType::Ground;
      }
      else if (branchOn < 2)
      {
        type = BlockType::Water;
      }
      else if (branchOn < 3)
      {
        type = BlockType::Sand;
      }
      else if (branchOn < 4)
      {
        type = BlockType::Wood;
      }
      else if (branchOn < 5)
      {
        type = BlockType::Flowers;
      }
      else if (branchOn < 6)
      {
        type = BlockType::Ruby;
      }
      else if (branchOn < 7)
      {
        type = BlockType::Leaves;
      }
      else if (branchOn < 8)
      {
        type = BlockType::Stone;
      }
      else if (branchOn < 9)
      {
        type = BlockType::Grass;
      }
      else if (branchOn < 10)
      {
        type = BlockType::Brick;
      }
      else
      {
        type = BlockType::Party;
      }

      int height = noise2d(i, j, 8, 32);
      for (int k = height; k >= 0; k--)
      {
        cm->set(i, k, j, type);
      }
    }
  }
}

void GameLoopCanvas::GameInit()
{
  m_spinTimer.Start(100); // in milliseconds.
  chunk_manager = new ChunkManager();

  GenerateBlocks(chunk_manager);
  moves = {std::make_pair(Direction::FORWARD, false),
           std::make_pair(Direction::BACKWARD, false),
           std::make_pair(Direction::UP, false),
           std::make_pair(Direction::DOWN, false),
           std::make_pair(Direction::RIGHT, false),
           std::make_pair(Direction::LEFT, false)};
  position = glm::vec3(3, chunk_manager->BOUNDY / 4, 3);
  player_angle = glm::vec3(0, -0.5, 0);
  up = glm::vec3(0, 1, 0);
  VectorUpdate(player_angle);
  steal_mouse = true;
  mouse_changed = false;
}

// Needed to use wxGetApp(). Usually you get the same result
// by using wxIMPLEMENT_APP(), but that can only be in main.
DECLARE_APP(MyApp);

void GameLoopCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
  // This is required even though dc is not used otherwise.
  wxPaintDC dc(this);
  Render();
}

void GameLoopCanvas::Resize()
{
  auto ClientSize = GetClientSize();
  glViewport(0, 0, ClientSize.x, ClientSize.y);
}

void GameLoopCanvas::OnKeyDown(wxKeyEvent& event)
{
  LOG(DEBUG) << "GameLoopCanvas::" << __FUNCTION__;

  switch (event.GetKeyCode())
  {
  case WXK_RIGHT:
  case 'D':
    moves[Direction::RIGHT] = true;
    break;

  case WXK_LEFT:
  case 'A':
    moves[Direction::LEFT] = true;
    break;

  case WXK_UP:
  case 'W':
    moves[Direction::FORWARD] = true;
    break;

  case WXK_DOWN:
  case 'S':
    moves[Direction::BACKWARD] = true;
    break;

  case 'K':
    moves[Direction::UP] = true;
    break;

  case 'J':
    moves[Direction::DOWN] = true;
    break;

  case WXK_ESCAPE:
    // Toggle stealing the mouse.
    steal_mouse = (steal_mouse) ? false : true;
    break;

  default:
    event.Skip();
    return;
  }
}

void GameLoopCanvas::OnKeyUp(wxKeyEvent& event)
{
  switch (event.GetKeyCode())
  {
  case WXK_RIGHT:
  case 'D':
    moves[Direction::RIGHT] = false;
    break;

  case WXK_LEFT:
  case 'A':
    moves[Direction::LEFT] = false;
    break;

  case WXK_UP:
  case 'W':
    moves[Direction::FORWARD] = false;
    break;

  case WXK_DOWN:
  case 'S':
    moves[Direction::BACKWARD] = false;
    break;

  case 'K':
    moves[Direction::UP] = false;
    break;

  case 'J':
    moves[Direction::DOWN] = false;
    break;

  default:
    event.Skip();
    return;
  }
}

void GameLoopCanvas::OnGameTimer(wxTimerEvent& WXUNUSED(event))
{
  Update();
  Render();
}

void GameLoopCanvas::Render()
{
  // With perspective OpenGL graphics, the wxFULL_REPAINT_ON_RESIZE style
  // flag should always be set, because even making the canvas smaller should
  // be followed by a paint event that updates the entire canvas with new
  // viewport settings.
  Resize();

  // Clear screen.
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // The context contains all the graphics utils.
  GraphicsContext& context = wxGetApp().GetContext(this);

  auto Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

  // Camera matrix
  auto View = glm::lookAt(position, position + lookat, up);
  // Just generate our view and projection; the model will be chosen
  // by individual chunks.
  auto VP = Projection * View;

  chunk_manager->render(context, VP);

  SwapBuffers();
}

void GameLoopCanvas::Update()
{
  VectorUpdate(player_angle);
  chunk_manager->update();
}

void GameLoopCanvas::VectorUpdate(glm::vec3 angle)
{

  // We want the forward and right vectors to be updated based on
  // where the player is rotated.
  forward.x = sinf(angle.x);
  forward.y = 0;
  forward.z = cosf(angle.x);

  right.x = -cosf(angle.x);
  right.y = 0;
  right.z = sinf(angle.x);

  lookat.x = sinf(angle.x) * cosf(angle.y);
  lookat.y = sinf(angle.y);
  lookat.z = cosf(angle.x) * cosf(angle.y);

  for (const auto& move : moves)
  {
    if (move.second)
    {
      switch (move.first)
      {
      case Direction::RIGHT:
        position += right * player_speed;
        break;
      case Direction::LEFT:
        position -= right * player_speed;
        break;
      case Direction::FORWARD:
        position += forward * player_speed;
        break;
      case Direction::BACKWARD:
        position -= forward * player_speed;
        break;
      case Direction::UP:
        position += up * player_speed;
        break;
      case Direction::DOWN:
        position -= up * player_speed;
        break;
      }
    }
  }
}

void GameLoopCanvas::OnMouseUpdate(wxMouseEvent& event)
{
  if (steal_mouse)
  {
    // Ignore every other mouse event so the mouse has a chance to
    // change before being warped to the center.
    if (mouse_changed)
    {
      mouse_changed = false;
      auto x = event.GetPosition().x;
      auto y = event.GetPosition().y;
      auto size = GetSize();

      // Update the angle the player is facing.
      player_angle.x -= (x - (size.x / 2)) * 0.001;
      player_angle.y -= (y - (size.y / 2)) * 0.001;

      // Check if the x angle has gone full circle.
      player_angle.x += (player_angle.x < -M_PI) ? 2 * M_PI : 0;
      player_angle.x -= (player_angle.x > M_PI) ? 2 * M_PI : 0;

      // Stop the y angle from going over 90 degrees away from the
      // horizontal.
      player_angle.y =
        (player_angle.y < -M_PI / 2) ? -M_PI / 2 : player_angle.y;
      player_angle.y = (player_angle.y > M_PI / 2) ? M_PI / 2 : player_angle.y;

      WarpPointer(size.x / 2, size.y / 2);
    }
    else
    {
      mouse_changed = true;
    }
  }
}
