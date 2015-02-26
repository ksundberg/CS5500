#ifndef _CANVAS_HEADER_
#define _CANVAS_HEADER_
#include <wxwidget.h>
#include "main.h"
#include "chunkmanager.h"

class TestGLCanvas : public wxGLCanvas
{
public:
  TestGLCanvas(wxWindow* parent, int* attribList = NULL);
  ~TestGLCanvas();

private:
  void OnPaint(wxPaintEvent& event);
  void Resize();
  void Spin(float xSpin, float ySpin);
  void OnKeyDown(wxKeyEvent& event);
  void OnSpinTimer(wxTimerEvent& WXUNUSED(event));
  void Render();
  void Update();
  void GameInit();
  void VectorUpdate(glm::vec3 angle);

  // angles of rotation around x- and y- axis
  const float player_speed = 0.5;
  float background_color;
  wxTimer m_spinTimer;
  ChunkManager* chunk_manager;
  glm::vec3 position;
  glm::vec3 forward;
  glm::vec3 right;
  glm::vec3 up;
  glm::vec3 lookat;
  glm::vec3 angle;

  wxDECLARE_EVENT_TABLE();
};

#endif
