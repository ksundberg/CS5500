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

#if (GLM_VERSION == 96)
typedef glm::tvec4<GLbyte> byte4;
#elif(GLM_VERSION == 95)
typedef glm::detail::tvec4<GLbyte, glm::mediump> byte4;
#else
typedef glm::detail::tvec4<GLbyte> byte4;
#endif

// the rendering context used by all GL canvases
class GraphicsContext : public wxGLContext
{
public:
  GraphicsContext(wxGLCanvas* canvas);
  ~GraphicsContext();

  GLuint shaderProgram();
  GLuint attributeCoord();
  GLuint mvp();

private:
  void initRendering();
  GLuint shader_program;
  GLuint texture;
};

#endif
