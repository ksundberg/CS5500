#include "logger.h"
#include "main.h"

bool MyApp::OnInit()
{
  if (!wxApp::OnInit()) return false;

  init_log();
  LOG(INFO) << "Initializing";

  frame.reset(
    new MainWindow(wxT("Hello World"), wxPoint(50, 50), wxSize(300, 400)));
  manager.reset(new ChunkManager());

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

IMPLEMENT_APP(MyApp);
