#ifndef _CANVAS_HEADER_
#define _CANVAS_HEADER_
#include <wxwidget.h>
#include <wx/glcanvas.h>

// the rendering context used by all GL canvases
class TestGLContext : public wxGLContext
{
public:
  TestGLContext(wxGLCanvas* canvas);

  // render the cube showing it at given angles
  void DrawRotatedCube(float xangle, float yangle);

private:
  // textures for the cube faces
  GLuint m_textures[6];
};

// Define a new application type
class MyApp : public wxApp
{
public:
  MyApp()
  {
    m_glContext = NULL;
    m_glStereoContext = NULL;
  }

  // Returns the shared context used by all frames and sets it as current for
  // the given canvas.
  TestGLContext& GetContext(wxGLCanvas* canvas);

  // virtual wxApp methods
  virtual bool OnInit();
  virtual int OnExit();

private:
  // the GL context we use for all our mono rendering windows
  TestGLContext* m_glContext;
  // the GL context we use for all our stereo rendering windows
  TestGLContext* m_glStereoContext;
};

// Define a new frame type
class MyFrame : public wxFrame
{
public:
  MyFrame(bool stereoWindow = false);

private:
  void OnClose(wxCommandEvent& event);

  wxDECLARE_EVENT_TABLE();
};

class TestGLCanvas : public wxGLCanvas
{
public:
  TestGLCanvas(wxWindow* parent, int* attribList = NULL);

private:
  void OnPaint(wxPaintEvent& event);
  void Spin(float xSpin, float ySpin);
  void OnKeyDown(wxKeyEvent& event);
  void OnSpinTimer(wxTimerEvent& WXUNUSED(event));

  // angles of rotation around x- and y- axis
  float m_xangle, m_yangle;

  wxTimer m_spinTimer;

  wxDECLARE_EVENT_TABLE();
};


#endif
