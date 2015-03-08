#include <wxwidget.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "graphics.h"
#include "textures.h"

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
static GLuint loadShaders(const char* vertex_file_path,
                          const char* fragment_file_path)
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

void GraphicsContext::initRendering()
{
  // set up the parameters we want to use
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  // Inititialize GLEW.
  if (glewInit() != GLEW_OK)
  {
    std::cout << "Failed to initialize GLEW." << std::endl;
    return;
  }

  // Load shaders.
  shader_program = loadShaders("world.v.glsl", "world.f.glsl");
  glUseProgram(shader_program);

  // Lets us send vertices to the shaders.
  auto attribute_coord = attributeCoord();
  glEnableVertexAttribArray(attribute_coord);

  glClearColor(0.8, 0.6, 0.7, 1.0);

  // Send textures to shaders.
  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_RGBA,
               Texture::atlas.width,
               Texture::atlas.height,
               0,
               GL_RGBA,
               GL_UNSIGNED_BYTE,
               Texture::atlas.pixel_data);
  glGenerateMipmap(GL_TEXTURE_2D);
}

GraphicsContext::GraphicsContext(wxGLCanvas* canvas) : wxGLContext(canvas)
{
  SetCurrent(*canvas);

  CheckGLError();
  initRendering();
}

GraphicsContext::~GraphicsContext()
{
  glDeleteProgram(shader_program);
}

GLuint GraphicsContext::shaderProgram()
{
  return shader_program;
}

GLuint GraphicsContext::attributeCoord()
{
  return glGetAttribLocation(shader_program, "coord");
}

GLuint GraphicsContext::mvp()
{
  return glGetUniformLocation(shader_program, "mvp");
}
