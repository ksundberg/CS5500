#include <wxwidget.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "graphics.h"

// ----------------------------------------------------------------------------
// helper functions
// ----------------------------------------------------------------------------

static void CheckGLError()
{
  GLenum errLast = GL_NO_ERROR;

  while (true)
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

// Function sourced from the tutorial code here:
// http://www.opengl-tutorial.org/download/
static GLuint loadShaders(const char* vertex_file_path, const char* fragment_file_path)
{

  // Create the shaders
  GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

  // Read the Vertex Shader code from the file
  std::string VertexShaderCode;
  std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
  if (VertexShaderStream.is_open())
  {
    std::string Line = "";
    while (getline(VertexShaderStream, Line))
      VertexShaderCode += "\n" + Line;
    VertexShaderStream.close();
  }
  else
  {
    printf("Impossible to open %s. Are you in the right directory?",
           vertex_file_path);
    getchar();
    return 0;
  }

  // Read the Fragment Shader code from the file
  std::string FragmentShaderCode;
  std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
  if (FragmentShaderStream.is_open())
  {
    std::string Line = "";
    while (getline(FragmentShaderStream, Line))
      FragmentShaderCode += "\n" + Line;
    FragmentShaderStream.close();
  }

  GLint Result = GL_FALSE;
  int InfoLogLength;

  // Compile Vertex Shader
  printf("Compiling shader : %s\n", vertex_file_path);
  char const* VertexSourcePointer = VertexShaderCode.c_str();
  glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
  glCompileShader(VertexShaderID);

  // Check Vertex Shader
  glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0)
  {
    std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
    glGetShaderInfoLog(
      VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    printf("%s\n", &VertexShaderErrorMessage[0]);
  }

  // Compile Fragment Shader
  printf("Compiling shader : %s\n", fragment_file_path);
  char const* FragmentSourcePointer = FragmentShaderCode.c_str();
  glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
  glCompileShader(FragmentShaderID);

  // Check Fragment Shader
  glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0)
  {
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
    glGetShaderInfoLog(
      FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
    printf("%s\n", &FragmentShaderErrorMessage[0]);
  }

  // Link the program
  printf("Linking program\n");
  GLuint ProgramID = glCreateProgram();
  glAttachShader(ProgramID, VertexShaderID);
  glAttachShader(ProgramID, FragmentShaderID);
  glLinkProgram(ProgramID);

  // Check the program
  glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
  glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0)
  {
    std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
    glGetProgramInfoLog(
      ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    printf("%s\n", &ProgramErrorMessage[0]);
  }

  glDeleteShader(VertexShaderID);
  glDeleteShader(FragmentShaderID);

  return ProgramID;
}

void TestGLContext::initRendering()
{
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
  glLoadIdentity(); // Reset the camera.
  glFrustum(-0.5f, 0.5f, -0.5f, 0.5f, 1.0f, 3.0f);


  // Inititialize GLEW.
  if (glewInit() != GLEW_OK)
  {
    std::cout << "Failed to initialize GLEW." << std::endl;
    return;
  }

  // Load shaders.
  std::cout << "Dear lord why." << std::endl;
  shader_program = loadShaders("world.v.glsl", "world.f.glsl");
  glUseProgram(shader_program);
  std::cout << "Dear lord why again." << std::endl;

  // Background color
  glClearColor(255.0, 100.0, 100.0, 1.0);
}

// function to draw the texture for cube faces
static wxImage DrawDice(int size)
{
  wxBitmap bmp(size, size);
  wxMemoryDC dc;
  dc.SelectObject(bmp);
  dc.SetBackground(*wxWHITE_BRUSH);
  dc.Clear();
  dc.SetBrush(*wxCYAN_BRUSH);
  dc.DrawRectangle(wxRect(0, 0, size / 2, size / 2));

  dc.SelectObject(wxNullBitmap);

  return bmp.ConvertToImage();
}

// ----------------------------------------------------------------------------
// TestGLContext
// ----------------------------------------------------------------------------

TestGLContext::TestGLContext(wxGLCanvas* canvas) : wxGLContext(canvas)
{
  SetCurrent(*canvas);

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

    const wxImage img(DrawDice(256));

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
  initRendering();
}

void TestGLContext::DrawRotatedCube(
  float xangle, float yangle, float xtranslate, float ytranslate, float length)
{
  auto size = length / 2;
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(xtranslate, ytranslate, -2.0f);
  glRotatef(xangle, 1.0f, 0.0f, 0.0f);
  glRotatef(yangle, 0.0f, 1.0f, 0.0f);

  // Draw the 6 faces of a cube.
  glBindTexture(GL_TEXTURE_2D, m_textures[0]);
  glBegin(GL_QUADS);
  glNormal3f(0.0f, 0.0f, 1.0f);
  glTexCoord2f(0, 0);
  glVertex3f(size, size, size);
  glTexCoord2f(1, 0);
  glVertex3f(-size, size, size);
  glTexCoord2f(1, 1);
  glVertex3f(-size, -size, size);
  glTexCoord2f(0, 1);
  glVertex3f(size, -size, size);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, m_textures[1]);
  glBegin(GL_QUADS);
  glNormal3f(0.0f, 0.0f, -1.0f);
  glTexCoord2f(0, 0);
  glVertex3f(-size, -size, -size);
  glTexCoord2f(1, 0);
  glVertex3f(-size, size, -size);
  glTexCoord2f(1, 1);
  glVertex3f(size, size, -size);
  glTexCoord2f(0, 1);
  glVertex3f(size, -size, -size);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, m_textures[2]);
  glBegin(GL_QUADS);
  glNormal3f(0.0f, 1.0f, 0.0f);
  glTexCoord2f(0, 0);
  glVertex3f(size, size, size);
  glTexCoord2f(1, 0);
  glVertex3f(size, size, -size);
  glTexCoord2f(1, 1);
  glVertex3f(-size, size, -size);
  glTexCoord2f(0, 1);
  glVertex3f(-size, size, size);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, m_textures[3]);
  glBegin(GL_QUADS);
  glNormal3f(0.0f, -1.0f, 0.0f);
  glTexCoord2f(0, 0);
  glVertex3f(-size, -size, -size);
  glTexCoord2f(1, 0);
  glVertex3f(size, -size, -size);
  glTexCoord2f(1, 1);
  glVertex3f(size, -size, size);
  glTexCoord2f(0, 1);
  glVertex3f(-size, -size, size);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, m_textures[4]);
  glBegin(GL_QUADS);
  glNormal3f(1.0f, 0.0f, 0.0f);
  glTexCoord2f(0, 0);
  glVertex3f(size, size, size);
  glTexCoord2f(1, 0);
  glVertex3f(size, -size, size);
  glTexCoord2f(1, 1);
  glVertex3f(size, -size, -size);
  glTexCoord2f(0, 1);
  glVertex3f(size, size, -size);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, m_textures[5]);
  glBegin(GL_QUADS);
  glNormal3f(-1.0f, 0.0f, 0.0f);
  glTexCoord2f(0, 0);
  glVertex3f(-size, -size, -size);
  glTexCoord2f(1, 0);
  glVertex3f(-size, -size, size);
  glTexCoord2f(1, 1);
  glVertex3f(-size, size, size);
  glTexCoord2f(0, 1);
  glVertex3f(-size, size, -size);
  glEnd();

  glFlush();

  CheckGLError();
}
