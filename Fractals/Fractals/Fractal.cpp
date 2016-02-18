#include "Fractal.h"

Color::Color() : r(0.0), g(0.0), b(0.0) {}
Color::Color(double rin, double gin, double bin) : r(rin), g(gin), b(bin) {}

Fractal::Fractal(int width, int height)
    : width_(width), height_(height), center_x_(0.0), center_y_(0.0),
      max_distance_sqr_(4.0), max_iteration_(32) {
  pixel_size_ = 4.0 / width_;
}

Fractal::~Fractal() {}

void Fractal::Initialize() {
  RecalcMins();
  CreateColors();
  CalculateEscapeTime();
}

void Fractal::CreateColors() {
  int i;
  double r, g, b;

  colors_.resize(max_iteration_ + 1);
  for (i = 0; i < max_iteration_; i++) {
    r = 1.0 * i / (double) max_iteration_;
    g = 0.5 * i / (double) max_iteration_;
    b = 1.0 * i / (double) max_iteration_;
    colors_[i] = Color(r, g, b);
  }
  colors_[max_iteration_] = Color(0.0, 0.0, 0.0);
}

void Fractal::CalculateEscapeTime() {
  int i, j;
  double x, y, xmin, ymin;

  xmin = center_x_ - pixel_size_ * (width_ / 2.0 - 0.5);
  ymin = center_y_ - pixel_size_ * (height_ / 2.0 - 0.5);
  escape_times_.resize(height_);
  for (j = 0; j < height_; j++) {
    escape_times_[j].resize(width_);
    for (i = 0; i < width_; i++) {
      x = xmin + i * pixel_size_;
      y = ymin + j * pixel_size_;
      escape_times_[j][i] = EscapeOne(x, y);
    }
  }
}

void Fractal::Draw() {
  int x, y, iter;

  for (y = 0; y < height_; y++) {
    for (x = 0; x < width_; x++) {
      iter = escape_times_[y][x];
      glColor3d(colors_[iter].r, colors_[iter].g, colors_[iter].b);
      glBegin(GL_POINTS);
      glVertex2d(x, y);
      glEnd();
    }
  }
}

void Fractal::Center(double x, double y) {
  RecalcCenter(x, y);
  RecalcMins();
  CalculateEscapeTime();
}

void Fractal::ZoomIn(double x, double y) {
  RecalcCenter(x, y);
  pixel_size_ /= 2.0;
  RecalcMins();
  CalculateEscapeTime();
}

void Fractal::ZoomOut(double x, double y) {
  RecalcCenter(x, y);
  pixel_size_ *= 2.0;
  RecalcMins();
  CalculateEscapeTime();
}

void Fractal::RecalcCenter(double x, double y) {
  center_x_ = min_x_ + pixel_size_ * x;
  center_y_ = min_y_ + pixel_size_ * y;
}

void Fractal::RecalcMins() {
  min_x_ = center_x_ - pixel_size_ * (width_ / 2.0 - 0.5);
  min_y_ = center_y_ - pixel_size_ * (height_ / 2.0 - 0.5);
}
