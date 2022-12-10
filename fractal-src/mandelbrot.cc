#include "mandelbrot.h"

Mandelbrot::Mandelbrot(int width, int height) : Fractal(width, height) {}
Mandelbrot::~Mandelbrot() {}

int Mandelbrot::EscapeOne(double x0, double y0) {
  int i;
  double x, y, x2, y2, xtmp, ytmp;

  x = y = 0.0;
  for (i = 0; i < max_iteration_; i++) {
    x2 = x * x;
    y2 = y * y;
    if(x2 + y2 > max_distance_sqr_) {
      break;
    }
    xtmp = x2 - y2 + x0;
    ytmp = 2.0 * x * y + y0;
    x = xtmp;
    y = ytmp;
  }

  return i;
}
