#include "logger.h"
#include "main.h"

#include <algorithm>

bool MyApp::OnInit()
{
  if (!wxApp::OnInit()) return false;

  init_log();

  world = World::Generate(100, 11, 5);

  frame = new MainWindow(
    wxT("Hello World"), world, wxPoint(50, 50), wxSize(300, 400));
  return true;
}

int MyApp::OnExit()
{
  return wxApp::OnExit();
}

GraphicsContext& MyApp::GetContext(wxGLCanvas* canvas)
{
  if (!m_glContext) m_glContext = std::make_shared<GraphicsContext>(canvas);

  m_glContext->SetCurrent(*canvas);
  return *m_glContext;
}

IMPLEMENT_APP(MyApp);
