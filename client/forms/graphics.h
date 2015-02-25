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

  // render the cube showing it at given angles
  void DrawRotatedCube(
    float xangle, float yangle, float xtranslate, float ytranslate, float size);

  GLuint shaderProgram();
private:
  void initRendering();
  // textures for the cube faces
  GLuint m_textures[6];
  GLuint shader_program;
};

#endif
