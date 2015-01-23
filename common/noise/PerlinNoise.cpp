#include <iostream>
#include "PerlinNoise.h"
#include "tbb/tbb.h"

PerlinNoise::PerlinNoise(uint seed)
{
  std::default_random_engine generator;
  generator.seed(seed);
  initialize(generator);
}

PerlinNoise::PerlinNoise()
{

  std::random_device rd;
  std::default_random_engine generator(rd());
  initialize(generator);
}

PerlinNoise::~PerlinNoise()
{
}

void PerlinNoise::initialize(std::default_random_engine generator)
{
  grad.push_back({1.0, 1.0, 0.0});
  grad.push_back({-1.0, 1.0, 0.0});
  grad.push_back({1.0, -1.0, 0.0});
  grad.push_back({-1.0, -1.0, 0.0});

  grad.push_back({1.0, 0.0, 1.0});
  grad.push_back({-1.0, 0.0, 1.0});
  grad.push_back({1.0, 0.0, -1.0});
  grad.push_back({-1.0, 0.0, -1.0});

  grad.push_back({0.0, 1.0, 1.0});
  grad.push_back({0.0, -1.0, 1.0});
  grad.push_back({0.0, 1.0, -1.0});
  grad.push_back({0.0, -1.0, -1.0});

  grad.push_back({1.0, 1.0, 0.0});
  grad.push_back({-1.0, 1.0, 0.0});
  grad.push_back({0.0, -1.0, 1.0});
  grad.push_back({0.0, -1.0, -1.0});

  for (int i = 0; i < 16; i++)
    phi.push_back(i);

  // shuffle phi
  std::shuffle(phi.begin(), phi.begin() + 14, generator); // 15?
}

double PerlinNoise::omega(double t) const
{
  t = (t > 0.0) ? t : -t;
  return (-6.0 * t * t * t * t * t + 15.0 * t * t * t * t - 10.0 * t * t * t +
          1.0);
}

vector3d PerlinNoise::gamma(int i, int j, int k) const
{
  int index;
  index = phi[abs(k) % 16];
  index = phi[abs(j + index) % 16];
  index = phi[abs(i + index) % 16];
  return grad[index];
}

double PerlinNoise::knot(int i, int j, int k, vector3d& v) const
{
  return (omega(v[0]) * omega(v[1]) * omega(v[2]) *
          (this->dot(gamma(i, j, k), v)));
}

double PerlinNoise::dot(vector3d left, vector3d right) const
{
  return left[0] * right[0] + left[1] * right[1] + left[2] * right[2];
}

double PerlinNoise::turbulence2D(double x, double y, int depth) const
{
  return this->turbulence3D(x, y, 1.0, depth);
}

double PerlinNoise::turbulence3D(double x, double y, double z, int depth) const
{

  double sum = 0.0;
  double weight = 1.0;
  vector3d pTemp = {x, y, z};

  sum = fabs(noise(pTemp));

  for (int i = 1; i < depth; i++)
  {
    weight = weight * 2;
    double xt = x * weight;
    double yt = y * weight;
    double zt = z * weight;

    pTemp = {xt, yt, zt};

    sum += fabs(noise(pTemp)) / weight;
  }

  return sum;
}

std::mutex matrixMutex3D;

void setOneCell3D(const PerlinNoise* perlin,
                  std::shared_ptr<matrix3d> matrix,
                  int i,
                  int j,
                  int k,
                  int width,
                  int height,
                  int depth,
                  int perlinDepth)
{
  double x = (double)i / (double)width;
  x = (x * 2) - 1.0;

  double y = (double)j / (double)height;
  y = (y * 2) - 1.0;

  double z = (double)k / (double)depth;
  z = (z * 2) - 1.0;

  auto p = perlin->turbulence3D(x, y, z, perlinDepth);

  (*matrix)[i][j][k] = p;
}

std::shared_ptr<matrix3d> PerlinNoise::createMatrix3D(int width,
                                                      int height,
                                                      int depth,
                                                      int perlinDepth) const
{
  auto matrix = std::make_shared<matrix3d>(
    width,
    std::vector<std::vector<double>>(height, std::vector<double>(depth)));

  tbb::parallel_for(tbb::blocked_range<int>(0, width),
                    [=](const tbb::blocked_range<int>& ri)
                    {
    for (int i = ri.begin(); i != ri.end(); i++)
    {
      tbb::parallel_for(tbb::blocked_range<int>(0, height),
                        [=](const tbb::blocked_range<int>& rj)
                        {
        for (int j = rj.begin(); j < rj.end(); j++)
        {
          tbb::parallel_for(tbb::blocked_range<int>(0, depth),
                            [=](const tbb::blocked_range<int>& rk)
                            {
            for (int k = rk.begin(); k != rk.end(); k++)
            {
              setOneCell3D(
                this, matrix, i, j, k, width, height, depth, perlinDepth);
            }
          });
        }
      });
    }

  });

  return matrix;
}

std::mutex matrixMutex2D;
void setOneCell2D(const PerlinNoise* perlin,
                  std::shared_ptr<matrix2d> matrix,
                  int i,
                  int j,
                  int width,
                  int height,
                  int perlinDepth)
{
  double x = (double)i / (double)width;
  x = (x * 2) - 1.0;

  double y = (double)j / (double)height;
  y = (y * 2) - 1.0;

  double noise = perlin->turbulence2D(x, y, perlinDepth);
  {
    std::lock_guard<std::mutex> locker(matrixMutex2D);
    (*matrix)[i][j] = noise;
  }
}

std::shared_ptr<matrix2d> PerlinNoise::createMatrix2D(int width,
                                                      int height,
                                                      int perlinDepth) const
{
  auto matrix = std::make_shared<matrix2d>(width, std::vector<double>(height));
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(-1.0, 1.0);

  tbb::parallel_for(tbb::blocked_range<int>(0, width),
                    [=](const tbb::blocked_range<int>& ri)
                    {
    for (int i = ri.begin(); i != ri.end(); i++)
    {
      tbb::parallel_for(tbb::blocked_range<int>(0, height),
                        [=](const tbb::blocked_range<int>& rj)
                        {
        for (int j = rj.begin(); j != rj.end(); j++)
          setOneCell2D(this, matrix, i, j, width, height, perlinDepth);

      });
    }
  });

  return matrix;
}

double PerlinNoise::noise(const vector3d& p) const
{
  int fi, fj, fk;
  double fu, fv, fw, sum;

  vector3d v;

  fi = int(floor(p[0]));
  fj = int(floor(p[1]));
  fk = int(floor(p[2]));

  fu = p[0] - double(fi);
  fv = p[1] - double(fj);
  fw = p[2] - double(fk);

  sum = 0.0;

  v = {fu, fv, fw};
  sum += knot(fi, fj, fk, v);

  v = {fu - 1, fv, fw};
  sum += knot(fi + 1, fj, fk, v);

  v = {fu, fv - 1, fw};
  sum += knot(fi, fj + 1, fk, v);

  v = {fu, fv, fw - 1};
  sum += knot(fi, fj, fk + 1, v);

  v = {fu - 1, fv - 1, fw};
  sum += knot(fi + 1, fj + 1, fk, v);

  v = {fu - 1, fv, fw - 1};
  sum += knot(fi + 1, fj, fk + 1, v);

  v = {fu, fv - 1, fw - 1};
  sum += knot(fi, fj + 1, fk + 1, v);

  v = {fu - 1, fv - 1, fw - 1};
  sum += knot(fi + 1, fj + 1, fk + 1, v);

  return sum;
}