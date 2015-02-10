#include "logger.h"
#include "canvas.h"
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#if !wxUSE_GLCANVAS
#error "OpenGL required: set wxUSE_GLCANVAS to 1 and rebuild the library"
#endif


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

  for (;;)
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

// function to draw the texture for cube faces
static wxImage DrawDice(int size, unsigned num)
{
  wxASSERT_MSG(num >= 1 && num <= 6, wxT("invalid dice index"));

  wxBitmap bmp(size, size);
  wxMemoryDC dc;
  dc.SelectObject(bmp);
  dc.SetBackground(*wxWHITE_BRUSH);
  dc.Clear();
  dc.SetBrush(*wxCYAN_BRUSH);
  dc.DrawRectangle(wxRect(0, 0, size/2, size/2));


  dc.SelectObject(wxNullBitmap);

  return bmp.ConvertToImage();
}

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// TestGLContext
// ----------------------------------------------------------------------------

TestGLContext::TestGLContext(wxGLCanvas* canvas) : wxGLContext(canvas)
{
  SetCurrent(*canvas);

  // set up the parameters we want to use
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_TEXTURE_2D);

  // add slightly more light, the default lighting is rather dark
  GLfloat ambient[] = {0.5, 0.5, 0.5, 0.5};
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

  // set viewing projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
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

void TestGLContext::DrawRotatedCube(float xangle, float yangle)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -2.0f);
  glRotatef(xangle, 1.0f, 0.0f, 0.0f);
  glRotatef(yangle, 0.0f, 1.0f, 0.0f);

  // draw six faces of a cube of size 1 centered at (0, 0, 0)
  glBindTexture(GL_TEXTURE_2D, m_textures[0]);
  glBegin(GL_QUADS);
  glNormal3f(0.0f, 0.0f, 1.0f);
  glTexCoord2f(0, 0);
  glVertex3f(0.5f, 0.5f, 0.5f);
  glTexCoord2f(1, 0);
  glVertex3f(-0.5f, 0.5f, 0.5f);
  glTexCoord2f(1, 1);
  glVertex3f(-0.5f, -0.5f, 0.5f);
  glTexCoord2f(0, 1);
  glVertex3f(0.5f, -0.5f, 0.5f);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, m_textures[1]);
  glBegin(GL_QUADS);
  glNormal3f(0.0f, 0.0f, -1.0f);
  glTexCoord2f(0, 0);
  glVertex3f(-0.5f, -0.5f, -0.5f);
  glTexCoord2f(1, 0);
  glVertex3f(-0.5f, 0.5f, -0.5f);
  glTexCoord2f(1, 1);
  glVertex3f(0.5f, 0.5f, -0.5f);
  glTexCoord2f(0, 1);
  glVertex3f(0.5f, -0.5f, -0.5f);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, m_textures[2]);
  glBegin(GL_QUADS);
  glNormal3f(0.0f, 1.0f, 0.0f);
  glTexCoord2f(0, 0);
  glVertex3f(0.5f, 0.5f, 0.5f);
  glTexCoord2f(1, 0);
  glVertex3f(0.5f, 0.5f, -0.5f);
  glTexCoord2f(1, 1);
  glVertex3f(-0.5f, 0.5f, -0.5f);
  glTexCoord2f(0, 1);
  glVertex3f(-0.5f, 0.5f, 0.5f);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, m_textures[3]);
  glBegin(GL_QUADS);
  glNormal3f(0.0f, -1.0f, 0.0f);
  glTexCoord2f(0, 0);
  glVertex3f(-0.5f, -0.5f, -0.5f);
  glTexCoord2f(1, 0);
  glVertex3f(0.5f, -0.5f, -0.5f);
  glTexCoord2f(1, 1);
  glVertex3f(0.5f, -0.5f, 0.5f);
  glTexCoord2f(0, 1);
  glVertex3f(-0.5f, -0.5f, 0.5f);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, m_textures[4]);
  glBegin(GL_QUADS);
  glNormal3f(1.0f, 0.0f, 0.0f);
  glTexCoord2f(0, 0);
  glVertex3f(0.5f, 0.5f, 0.5f);
  glTexCoord2f(1, 0);
  glVertex3f(0.5f, -0.5f, 0.5f);
  glTexCoord2f(1, 1);
  glVertex3f(0.5f, -0.5f, -0.5f);
  glTexCoord2f(0, 1);
  glVertex3f(0.5f, 0.5f, -0.5f);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, m_textures[5]);
  glBegin(GL_QUADS);
  glNormal3f(-1.0f, 0.0f, 0.0f);
  glTexCoord2f(0, 0);
  glVertex3f(-0.5f, -0.5f, -0.5f);
  glTexCoord2f(1, 0);
  glVertex3f(-0.5f, -0.5f, 0.5f);
  glTexCoord2f(1, 1);
  glVertex3f(-0.5f, 0.5f, 0.5f);
  glTexCoord2f(0, 1);
  glVertex3f(-0.5f, 0.5f, -0.5f);
  glEnd();

  glFlush();

  CheckGLError();
}

// ----------------------------------------------------------------------------
// MyApp: the application object
// ----------------------------------------------------------------------------

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
  if (!wxApp::OnInit()) return false;

  new MyFrame();

  return true;
}

int MyApp::OnExit()
{
  delete m_glContext;

  return wxApp::OnExit();
}

TestGLContext& MyApp::GetContext(wxGLCanvas* canvas)
{
  TestGLContext* glContext;
  if (!m_glContext)
  {
    // Create the OpenGL context for the first mono window which needs it:
    // subsequently created windows will all share the same context.
    m_glContext = new TestGLContext(canvas);
  }
  glContext = m_glContext;

  glContext->SetCurrent(*canvas);

  return *glContext;
}

// ----------------------------------------------------------------------------
// TestGLCanvas
// ----------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(TestGLCanvas, wxGLCanvas) EVT_PAINT(TestGLCanvas::OnPaint)
  EVT_KEY_DOWN(TestGLCanvas::OnKeyDown)
  EVT_TIMER(SpinTimer, TestGLCanvas::OnSpinTimer) wxEND_EVENT_TABLE()

  TestGLCanvas::TestGLCanvas(wxWindow* parent, int* attribList)
  // With perspective OpenGL graphics, the wxFULL_REPAINT_ON_RESIZE style
  // flag should always be set, because even making the canvas smaller should
  // be followed by a paint event that updates the entire canvas with new
  // viewport settings.
  : wxGLCanvas(parent,
               wxID_ANY,
               attribList,
               wxDefaultPosition,
               wxDefaultSize,
               wxFULL_REPAINT_ON_RESIZE),
    m_xangle(30.0),
    m_yangle(30.0),
    m_spinTimer(this, SpinTimer)
{
}

void TestGLCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
  // This is required even though dc is not used otherwise.
  wxPaintDC dc(this);

  // Set the OpenGL viewport according to the client size of this canvas.
  // This is done here rather than in a wxSizeEvent handler because our
  // OpenGL rendering context (and thus viewport setting) is used with
  // multiple canvases: If we updated the viewport in the wxSizeEvent
  // handler, changing the size of one canvas causes a viewport setting that
  // is wrong when next another canvas is repainted.
  const wxSize ClientSize = GetClientSize();

  TestGLContext& canvas = wxGetApp().GetContext(this);
  glViewport(0, 0, ClientSize.x, ClientSize.y);

  // Render the graphics and swap the buffers.
  canvas.DrawRotatedCube(m_xangle, m_yangle);
  SwapBuffers();
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
  if (v == 0)
  {
    // The error is not important. It is GL_INVALID_ENUM.
    // We just want to clear the error stack.
    glGetError();

    return wxString();
  }

  return wxString((const char*)v);
}

// ----------------------------------------------------------------------------
// MyFrame: main application window
// ----------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
  EVT_MENU(wxID_CLOSE, MyFrame::OnClose) wxEND_EVENT_TABLE()

  MyFrame::MyFrame(bool stereoWindow)
  : wxFrame(NULL, wxID_ANY, wxT("wxWidgets OpenGL Cube Sample"))
{
  int stereoAttribList[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_STEREO, 0};

  new TestGLCanvas(this, stereoWindow ? stereoAttribList : NULL);

  // Make a menubar
  wxMenu* menu = new wxMenu;
  menu->AppendSeparator();
  menu->Append(wxID_CLOSE);
  wxMenuBar* menuBar = new wxMenuBar;
  menuBar->Append(menu, wxT("&Cube"));

  SetMenuBar(menuBar);

  CreateStatusBar();

  SetClientSize(400, 400);
  Show();

  // test IsDisplaySupported() function:
  static const int attribs[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, 0};
  wxLogStatus("Double-buffered display %s supported",
              wxGLCanvas::IsDisplaySupported(attribs) ? "is" : "not");

}

void MyFrame::OnClose(wxCommandEvent& WXUNUSED(event))
{
  // true is to force the frame to close
  Close(true);
}
