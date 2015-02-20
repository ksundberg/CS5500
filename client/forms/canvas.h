#ifndef _CANVAS_HEADER_
#define _CANVAS_HEADER_
#include <wxwidget.h>
#include <wx/glcanvas.h>
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

  wxDECLARE_EVENT_TABLE();
};

// the rendering context used by all GL canvases
class TestGLContext : public wxGLContext
{
public:
  TestGLContext(wxGLCanvas* canvas);

  // render the cube showing it at given angles
  void DrawRotatedCube(
    float xangle, float yangle, float xtranslate, float ytranslate, float size);

private:
  // textures for the cube faces
  GLuint m_textures[6];
};

#endif
