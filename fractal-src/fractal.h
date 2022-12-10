#ifndef FRACTAL_H_
#define FRACTAL_H_

#include <vector>
#include <GL/glut.h>

struct Color {
 public:
  Color();
  Color(double rin, double gin, double bin);
  double r, g, b;
};

class Fractal {
 public:
  Fractal(int width, int height);
  virtual ~Fractal();
  virtual void Initialize();
  virtual void CreateColors();
  virtual void CalculateEscapeTime();
  virtual int EscapeOne(double x, double y) = 0;
  virtual void Draw();
  virtual void Center(double x, double y);
  virtual void ZoomIn(double x, double y);
  virtual void ZoomOut(double x, double y);

 protected:
  int width_, height_, max_iteration_;
  double center_x_, center_y_, min_x_, min_y_, pixel_size_, max_distance_sqr_;
  std::vector<Color> colors_;
  std::vector<std::vector<int>> escape_times_;

  virtual void RecalcCenter(double x, double y);
  virtual void RecalcMins();
};

#endif  // FRACTAL_H_
