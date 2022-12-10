#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <cstring>
#include <cmath>
#include <GL/glut.h>
#include "connect_four.h"

using namespace std;

const int STR_LEN = 50;
const int CURVE_RESOLUTION = 32;
const double PI = atan(1.0) * 4.0;

void DrawRectangle(double x1, double y1, double x2, double y2);
void DrawTriangle(double x1, double y1,
                  double x2, double y2,
                  double x3, double y3);
void DrawCircle(double x1, double y1, double radius);
void DrawText(double x, double y, char * string);
void display();
void keyboard(unsigned char c, int x, int y);
void reshape(int w, int h);
void mouse(int mouseButton, int state, int x, int y);

#endif  // GRAPHICS_H_
