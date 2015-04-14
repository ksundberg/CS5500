// Example application modified from the wxWidgets demo here:
// http://fossies.org/dox/wxWidgets-3.0.2/cube_8cpp_source.html
#include "logger.h"
#include "canvas.h"

BEGIN_EVENT_TABLE(GameLoopCanvas, wxGLCanvas)
EVT_PAINT(GameLoopCanvas::OnPaint) EVT_KEY_DOWN(GameLoopCanvas::OnKeyDown)
  EVT_CLOSE(GameLoopCanvas::OnClose) EVT_KEY_UP(GameLoopCanvas::OnKeyUp)
    EVT_MOTION(GameLoopCanvas::OnMouseUpdate) END_EVENT_TABLE()

      GameLoopCanvas::GameLoopCanvas(wxWindow* parent,
                                     std::shared_ptr<World> world,
                                     wxSize size,
                                     int* attribList)
  : wxGLCanvas(parent,
               wxID_ANY,
               attribList,
               wxDefaultPosition,
               size,
               wxFULL_REPAINT_ON_RESIZE)
  , world(world)
  , object_viewer(nullptr)
{
  GameInit();
}

GameLoopCanvas::~GameLoopCanvas()
{
}

void GameLoopCanvas::CreateChunks()
{
  LOG(INFO) << "Blocks count: " << world->blocks.size();
  for (auto& block : world->blocks)
    chunk_manager->set(block->position, block->type);
}

void GameLoopCanvas::GameInit()
{
  moves = {std::make_pair(Direction::FORWARD, false),
           std::make_pair(Direction::BACKWARD, false),
           std::make_pair(Direction::UP, false),
           std::make_pair(Direction::DOWN, false),
           std::make_pair(Direction::RIGHT, false),
           std::make_pair(Direction::LEFT, false)};
  chunk_manager = std::unique_ptr<ChunkManager>(new ChunkManager());
  CreateChunks();
  position = glm::vec3(3, 4, 3);
  player_angle = glm::vec3(0, -0.5, 0);
  up = glm::vec3(0, 1, 0);
  VectorUpdate(player_angle);
  steal_mouse = true;
  mouse_changed = false;
  render_loop_on = false;
  activateGameLoop(true);
}

// Needed to use GetApp(). Usually you get the same result
// by using IMPLEMENT_APP(), but that can only be in main.
DECLARE_APP(MyApp);

void GameLoopCanvas::OnPaint(wxPaintEvent&)
{
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

  case WXK_SPACE:
    moves[Direction::UP] = true;
    break;

  case WXK_SHIFT:
    moves[Direction::DOWN] = true;
    break;

  case WXK_ESCAPE:
    // Toggle stealing the mouse.
    steal_mouse = !steal_mouse;
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

  case WXK_SPACE:
    moves[Direction::UP] = false;
    break;

  case WXK_SHIFT:
    moves[Direction::DOWN] = false;
    break;

  default:
    event.Skip();
    return;
  }
}

void GameLoopCanvas::Render()
{
  // With perspective OpenGL graphics, the wxFULL_REPAINT_ON_RESIZE style
  // flag should always be set, because even making the canvas smaller should
  // be followed by a paint event that updates the entire canvas with new
  // viewport settings.
  Resize();

  // Clear screen.
  glClearColor(0, 0, 0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  auto Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 500.0f);
  auto View = glm::lookAt(position, position + lookat, up);
  auto VP = Projection * View;

  chunk_manager->render(wxGetApp().GetContext(this), VP);
  if (object_viewer == nullptr)
    object_viewer =
      std::unique_ptr<VertexViewer>(new VertexViewer(world->Containers()));
  object_viewer->Render(wxGetApp().GetContext(this), VP);

  SwapBuffers();
}

void GameLoopCanvas::Update()
{
  VectorUpdate(player_angle);
  chunk_manager->update();
  world->Update();
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
        position += lookat * player_speed;
        break;
      case Direction::BACKWARD:
        position -= lookat * player_speed;
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

void GameLoopCanvas::OnClose(wxCloseEvent& event)
{
  activateGameLoop(false);
  event.Skip();
}

void GameLoopCanvas::activateGameLoop(bool on)
{
  if (on && !render_loop_on)
  {
    Connect(wxID_ANY, wxEVT_IDLE, wxIdleEventHandler(GameLoopCanvas::OnIdle));
    render_loop_on = true;
  }
  else if (!on && render_loop_on)
  {
    Disconnect(wxEVT_IDLE, wxIdleEventHandler(GameLoopCanvas::OnIdle));
    render_loop_on = false;
  }
}

void GameLoopCanvas::OnIdle(wxIdleEvent& event)
{
  if (render_loop_on)
  {
    Render();
    Update();
    event.RequestMore();
  }
}
