#ifndef PerlinNoise_h
#define PerlinNoise_h

#include <algorithm>
#include <vector>
#include <array>
#include <random>
#include <memory>

typedef std::array<double, 3> vector3d;
typedef std::vector<std::vector<std::vector<double>>> matrix3d;
typedef std::vector<std::vector<double>> matrix2d;

class PerlinNoise
{
public:
  PerlinNoise();
  PerlinNoise(uint seed);
  ~PerlinNoise();

  double turbulence2D(double x, double y, int depth) const;
  double turbulence3D(double x, double y, double z, int depth) const;

  std::shared_ptr<matrix3d> createMatrix3D(int width,
                                           int height,
                                           int depth,
                                           int perlinDepth) const;
  std::shared_ptr<matrix2d> createMatrix2D(int width,
                                           int height,
                                           int perlinDepth) const;

private:
  void initialize(std::default_random_engine generator);
  double dot(vector3d left, vector3d right) const;
  double noise(const std::array<double, 3>& p) const;
  double omega(double t) const;
  std::array<double, 3> gamma(int i, int j, int k) const;
  double knot(int i, int j, int k, std::array<double, 3>& v) const;

  std::vector<vector3d> grad;
  std::vector<int> phi;
};

#endif