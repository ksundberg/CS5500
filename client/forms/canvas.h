#ifndef _CANVAS_HEADER_
#define _CANVAS_HEADER_
#include <wxwidget.h>
#include <map>
#include "main.h"
#include "chunkmanager.h"
#include "vertexviewer.h"

enum class Direction
{
  UP,
  DOWN,
  LEFT,
  RIGHT,
  FORWARD,
  BACKWARD
};

class GameLoopCanvas : public wxGLCanvas
{
public:
  GameLoopCanvas(wxWindow* parent,
                 std::shared_ptr<World> world,
                 wxSize size,
                 int* attribList = NULL);
  ~GameLoopCanvas();

private:
  void OnPaint(wxPaintEvent& event);
  void Resize();
  void Spin(float xSpin, float ySpin);
  void OnKeyDown(wxKeyEvent& event);
  void OnKeyUp(wxKeyEvent& event);
  void OnIdle(wxIdleEvent& event);
  void OnClose(wxCloseEvent& event);
  void activateGameLoop(bool on);
  void Render();
  void Update() override;
  void GameInit();
  void VectorUpdate(glm::vec3 angle);
  void OnMouseUpdate(wxMouseEvent& event);

  void CreateChunks();

  // angles of rotation around x- and y- axis
  const float player_speed = 0.7;
  bool steal_mouse;
  bool mouse_changed;
  bool render_loop_on;
  std::shared_ptr<World> world;
  std::unique_ptr<ChunkManager> chunk_manager;
  std::unique_ptr<IRenderable> object_viewer;
  glm::vec3 position;
  glm::vec3 forward;
  glm::vec3 right;
  glm::vec3 up;
  glm::vec3 lookat;
  glm::vec3 player_angle;
  std::map<Direction, bool> moves;

  DECLARE_EVENT_TABLE();
};

#endif
