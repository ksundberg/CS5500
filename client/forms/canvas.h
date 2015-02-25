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

  // angles of rotation around x- and y- axis
  float m_xangle, m_yangle;
  wxTimer m_spinTimer;
  ChunkManager* chunk_manager;
  glm::vec3 position; // Where are we in the voxel world.

  wxDECLARE_EVENT_TABLE();
};


#endif
