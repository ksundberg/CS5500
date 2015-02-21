#ifndef _GRAPHICS_HEADER_
#define _GRAPHICS_HEADER_
#include <wxwidget.h>
#include <wx/glcanvas.h>

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
