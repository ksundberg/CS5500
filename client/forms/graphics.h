#ifndef _GRAPHICS_HEADER_
#define _GRAPHICS_HEADER_
#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <wx/glcanvas.h>

typedef glm::detail::tvec4<GLbyte, glm::lowp> byte4;

// the rendering context used by all GL canvases
class GraphicsContext : public wxGLContext
{
public:
  GraphicsContext(wxGLCanvas* canvas);

  GLuint shaderProgram();
private:
  void initRendering();
  // textures for the cube faces
  GLuint shader_program;
};

#endif
