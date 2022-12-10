#ifndef MANDELBROT_H_
#define MANDELBROT_H_

#include "fractal.h"

class Mandelbrot : public Fractal {
 public:
  Mandelbrot(int width, int height);
  virtual ~Mandelbrot();
  virtual int EscapeOne(double x, double y);
};

#endif  // MANDELBROT_H_
