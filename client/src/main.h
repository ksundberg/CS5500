#ifndef _MAIN_HEADER_
#define _MAIN_HEADER_
#include <wxwidget.h>
#include "MainWindow.h"
#include "canvas.h"
#include "chunkmanager.h"

// Define a new application type
class MyApp : public wxApp
{
private:
  // the GL context we use for all our mono rendering windows
  TestGLContext* m_glContext;
  MainWindow* frame;
  ChunkManager* manager;

public:
  MyApp() { m_glContext = NULL; }

  // Returns the shared context used by all frames and sets it as current for
  // the given canvas.
  TestGLContext& GetContext(wxGLCanvas* canvas);

  // virtual wxApp methods
  virtual bool OnInit();
  virtual int OnExit();
};

#endif
