#ifndef _CANVAS_HEADER_
#define _CANVAS_HEADER_
#include "wxwidget.h"
#include <wx/glcanvas.h>

class TestGLCanvas : public wxGLCanvas
{
public:
  TestGLCanvas(wxWindow* parent, wxSize size, int* attribList = NULL);

private:
  void OnPaint(wxPaintEvent& event);
  void Resize();
  void Spin(float xSpin, float ySpin);
  void OnKeyDown(wxKeyEvent& event);
  void OnSpinTimer(wxTimerEvent& WXUNUSED(event));

  // angles of rotation around x- and y- axis
  float m_xangle, m_yangle;

  wxTimer m_spinTimer;

  DECLARE_EVENT_TABLE();
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
