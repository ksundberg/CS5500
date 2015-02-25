#ifndef _GRAPHICS_HEADER_
#define _GRAPHICS_HEADER_
#include <GL/glew.h>
#include <GL/glut.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <wx/glcanvas.h>

typedef glm::tvec4<GLbyte> byte4;

// the rendering context used by all GL canvases
class TestGLContext : public wxGLContext
{
public:
  TestGLContext(wxGLCanvas* canvas);

  GLuint shaderProgram();
private:
  void initRendering();
  // textures for the cube faces
  GLuint shader_program;
};

#endif
