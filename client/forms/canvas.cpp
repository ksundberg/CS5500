// Example application modified from the wxWidgets demo here:
// http://fossies.org/dox/wxWidgets-3.0.2/cube_8cpp_source.html

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "canvas.h"
#include "main.h"

// control ids
enum
{
  SpinTimer = wxID_HIGHEST + 1
};

// ----------------------------------------------------------------------------
// helper functions
// ----------------------------------------------------------------------------

static void CheckGLError()
{
  GLenum errLast = GL_NO_ERROR;

  while (true)
  {
    GLenum err = glGetError();
    if (err == GL_NO_ERROR) return;

    // normally the error is reset by the call to glGetError() but if
    // glGetError() itself returns an error, we risk looping forever here
    // so check that we get a different error than the last time
    if (err == errLast)
    {
      wxLogError(wxT("OpenGL error state couldn't be reset."));
      return;
    }

    errLast = err;

    wxLogError(wxT("OpenGL error %d"), err);
  }
}

static void initRendering()
{
  // set up the parameters we want to use
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_TEXTURE_2D);
}

// function to draw the texture for cube faces
static wxImage DrawDice(int size, unsigned num)
{
  (void)num;
  wxASSERT_MSG(num >= 1 && num <= 6, wxT("invalid dice index"));

  wxBitmap bmp(size, size);
  wxMemoryDC dc;
  dc.SelectObject(bmp);
  dc.SetBackground(*wxWHITE_BRUSH);
  dc.Clear();
  dc.SetBrush(*wxCYAN_BRUSH);
  dc.DrawRectangle(wxRect(0, 0, size / 2, size / 2));

  dc.SelectObject(wxNullBitmap);

  return bmp.ConvertToImage();
}

// ----------------------------------------------------------------------------
// TestGLContext
// ----------------------------------------------------------------------------

TestGLContext::TestGLContext(wxGLCanvas* canvas) : wxGLContext(canvas)
{
  SetCurrent(*canvas);
  initRendering();

  // add slightly more light, the default lighting is rather dark
  GLfloat ambient[] = {0.5, 0.5, 0.5, 0.5};
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

  // set viewing projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity(); // Reset the camera.
  glFrustum(-0.5f, 0.5f, -0.5f, 0.5f, 1.0f, 3.0f);

  // create the textures to use for cube sides: they will be reused by all
  // canvases (which is probably not critical in the case of simple textures
  // we use here but could be really important for a real application where
  // each texture could take many megabytes)
  glGenTextures(WXSIZEOF(m_textures), m_textures);

  for (unsigned i = 0; i < WXSIZEOF(m_textures); i++)
  {
    glBindTexture(GL_TEXTURE_2D, m_textures[i]);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    const wxImage img(DrawDice(256, i + 1));

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 img.GetWidth(),
                 img.GetHeight(),
                 0,
                 GL_RGB,
                 GL_UNSIGNED_BYTE,
                 img.GetData());
  }

  CheckGLError();
}

void TestGLContext::DrawRotatedCube(
  float xangle, float yangle, float xtranslate, float ytranslate, float length)
{
  auto size = length / 2;
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(xtranslate, ytranslate, -2.0f);
  glRotatef(xangle, 1.0f, 0.0f, 0.0f);
  glRotatef(yangle, 0.0f, 1.0f, 0.0f);

  // Draw the 6 faces of a cube.
  glBindTexture(GL_TEXTURE_2D, m_textures[0]);
  glBegin(GL_QUADS);
  glNormal3f(0.0f, 0.0f, 1.0f);
  glTexCoord2f(0, 0);
  glVertex3f(size, size, size);
  glTexCoord2f(1, 0);
  glVertex3f(-size, size, size);
  glTexCoord2f(1, 1);
  glVertex3f(-size, -size, size);
  glTexCoord2f(0, 1);
  glVertex3f(size, -size, size);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, m_textures[1]);
  glBegin(GL_QUADS);
  glNormal3f(0.0f, 0.0f, -1.0f);
  glTexCoord2f(0, 0);
  glVertex3f(-size, -size, -size);
  glTexCoord2f(1, 0);
  glVertex3f(-size, size, -size);
  glTexCoord2f(1, 1);
  glVertex3f(size, size, -size);
  glTexCoord2f(0, 1);
  glVertex3f(size, -size, -size);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, m_textures[2]);
  glBegin(GL_QUADS);
  glNormal3f(0.0f, 1.0f, 0.0f);
  glTexCoord2f(0, 0);
  glVertex3f(size, size, size);
  glTexCoord2f(1, 0);
  glVertex3f(size, size, -size);
  glTexCoord2f(1, 1);
  glVertex3f(-size, size, -size);
  glTexCoord2f(0, 1);
  glVertex3f(-size, size, size);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, m_textures[3]);
  glBegin(GL_QUADS);
  glNormal3f(0.0f, -1.0f, 0.0f);
  glTexCoord2f(0, 0);
  glVertex3f(-size, -size, -size);
  glTexCoord2f(1, 0);
  glVertex3f(size, -size, -size);
  glTexCoord2f(1, 1);
  glVertex3f(size, -size, size);
  glTexCoord2f(0, 1);
  glVertex3f(-size, -size, size);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, m_textures[4]);
  glBegin(GL_QUADS);
  glNormal3f(1.0f, 0.0f, 0.0f);
  glTexCoord2f(0, 0);
  glVertex3f(size, size, size);
  glTexCoord2f(1, 0);
  glVertex3f(size, -size, size);
  glTexCoord2f(1, 1);
  glVertex3f(size, -size, -size);
  glTexCoord2f(0, 1);
  glVertex3f(size, size, -size);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, m_textures[5]);
  glBegin(GL_QUADS);
  glNormal3f(-1.0f, 0.0f, 0.0f);
  glTexCoord2f(0, 0);
  glVertex3f(-size, -size, -size);
  glTexCoord2f(1, 0);
  glVertex3f(-size, -size, size);
  glTexCoord2f(1, 1);
  glVertex3f(-size, size, size);
  glTexCoord2f(0, 1);
  glVertex3f(-size, size, -size);
  glEnd();

  glFlush();

  CheckGLError();
}

// ----------------------------------------------------------------------------
// TestGLCanvas
// ----------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(TestGLCanvas, wxGLCanvas) EVT_PAINT(TestGLCanvas::OnPaint)
  EVT_KEY_DOWN(TestGLCanvas::OnKeyDown)
  EVT_TIMER(SpinTimer, TestGLCanvas::OnSpinTimer) wxEND_EVENT_TABLE()

  TestGLCanvas::TestGLCanvas(wxWindow* parent, int* attribList)
  : wxGLCanvas(parent,
               wxID_ANY,
               attribList,
               wxDefaultPosition,
               wxDefaultSize,
               wxFULL_REPAINT_ON_RESIZE)
  , m_xangle(30.0)
  , m_yangle(30.0)
  , m_spinTimer(this, SpinTimer)
{
}

// Needed to use wxGetApp(). Usually you get the same result
// by using wxIMPLEMENT_APP(), but that can only be in main.
wxDECLARE_APP(MyApp);

void TestGLCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
  // This is required even though dc is not used otherwise.
  wxPaintDC dc(this);

  // With perspective OpenGL graphics, the wxFULL_REPAINT_ON_RESIZE style
  // flag should always be set, because even making the canvas smaller should
  // be followed by a paint event that updates the entire canvas with new
  // viewport settings.
  Resize();

  // Clear screen.
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Render the graphics and swap the buffers.
  TestGLContext& canvas = wxGetApp().GetContext(this);
  canvas.DrawRotatedCube(m_xangle, m_yangle, 0.1f, -0.2f, 0.5f);
  canvas.DrawRotatedCube(m_xangle, m_yangle, -0.5f, 0.3f, 0.5f);
  SwapBuffers();
}

void TestGLCanvas::Resize()
{
  const wxSize ClientSize = GetClientSize();
  glViewport(0, 0, ClientSize.x, ClientSize.y);
}

void TestGLCanvas::Spin(float xSpin, float ySpin)
{
  m_xangle += xSpin;
  m_yangle += ySpin;

  Refresh(false);
}

void TestGLCanvas::OnKeyDown(wxKeyEvent& event)
{
  float angle = 5.0;

  switch (event.GetKeyCode())
  {
  case WXK_RIGHT:
    Spin(0.0, -angle);
    break;

  case WXK_LEFT:
    Spin(0.0, angle);
    break;

  case WXK_DOWN:
    Spin(-angle, 0.0);
    break;

  case WXK_UP:
    Spin(angle, 0.0);
    break;

  case WXK_SPACE:
    if (m_spinTimer.IsRunning())
      m_spinTimer.Stop();
    else
      m_spinTimer.Start(25);
    break;

  default:
    event.Skip();
    return;
  }
}

void TestGLCanvas::OnSpinTimer(wxTimerEvent& WXUNUSED(event))
{
  Spin(0.0, 4.0);
}

wxString glGetwxString(GLenum name)
{
  const GLubyte* v = glGetString(name);
  if (v == nullptr)
  {
    // The error is not important. It is GL_INVALID_ENUM.
    // We just want to clear the error stack.
    glGetError();

    return wxString();
  }

  return wxString((const char*)v);
}
