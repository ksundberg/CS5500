#ifndef _CANVAS_HEADER_
#define _CANVAS_HEADER_
#include <wxwidget.h>
#include "main.h"
#include "chunkmanager.h"

class GameLoopCanvas : public wxGLCanvas
{
public:
  GameLoopCanvas(wxWindow* parent, wxSize size, int* attribList = NULL);
  ~GameLoopCanvas();

private:
  void OnPaint(wxPaintEvent& event);
  void Resize();
  void Spin(float xSpin, float ySpin);
  void OnKeyDown(wxKeyEvent& event);
  void OnGameTimer(wxTimerEvent& WXUNUSED(event));
  void Render();
  void Update();
  void GameInit();
  void VectorUpdate(glm::vec3 angle);
  void OnMouseUpdate(wxMouseEvent& event);

  // angles of rotation around x- and y- axis
  const float player_speed = 0.5;
  bool steal_mouse;
  bool mouse_changed;
  wxTimer m_spinTimer;
  ChunkManager* chunk_manager;
  glm::vec3 position;
  glm::vec3 forward;
  glm::vec3 right;
  glm::vec3 up;
  glm::vec3 lookat;
  glm::vec3 player_angle;

  DECLARE_EVENT_TABLE();
};

#endif
