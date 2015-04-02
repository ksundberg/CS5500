#include "logger.h"
#include "main.h"

#include <algorithm>

#include <glm/gtc/noise.hpp>
#include "PerlinNoise.h"

bool MyApp::OnInit()
{
  if (!wxApp::OnInit()) return false;

  init_log();

  world = GenerateWorld();

  frame = std::make_shared<MainWindow>(
    wxT("Hello World"), world, wxPoint(50, 50), wxSize(300, 400));
  return true;
}

// TODO: move to a more model oriented data location
std::shared_ptr<ChunkManager> MyApp::GenerateWorld()
{
  PerlinNoise perlin;
  auto noiseMap = perlin.createMatrix2D(world->BOUNDX, world->BOUNDY, 5);
  auto world = std::make_shared<ChunkManager>();
  for (int i = 0; i < world->BOUNDX; i++)
    for (int j = 0; j < world->BOUNDY; j++)
    {
      int height = (*noiseMap)[i][j] * 11;
      for (int k = 0; k <= height; k++)
        world->set(i, k, j, BlockType(std::min(k,11)));
    }
  return world;
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
