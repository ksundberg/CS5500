#ifndef _MAIN_HEADER_
#define _MAIN_HEADER_
#include "MainWindow.h"
#include "graphics.h"
#include "chunkmanager.h"

// Define a new application type
class MyApp : public wxApp
{
private:
  // the GL context we use for all our mono rendering windows
  std::shared_ptr<GraphicsContext> m_glContext;
  std::shared_ptr<MainWindow> frame;

public:
  MyApp() : m_glContext(nullptr) {}

  // Returns the shared context used by all frames and sets it as current for
  // the given canvas.
  GraphicsContext& GetContext(wxGLCanvas* canvas);

  // virtual wxApp methods
  virtual bool OnInit();
  virtual int OnExit();
};

#endif
