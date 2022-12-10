#include <cmath>
#include <cstring>
#include "fractal.h"
#include "mandelbrot.h"

double screen_x = 700;
double screen_y = 500;
Fractal *g_fractal;

//
// Functions that draw basic primitives
//

void DrawCircle(double x1, double y1, double radius) {
  glBegin(GL_POLYGON);
  for (int i = 0; i < 32; i++) {
    double theta = (double) i / 32.0 * 2.0 * 3.1415926;
    double x = x1 + radius * cos(theta);
    double y = y1 + radius * sin(theta);
    glVertex2d(x, y);
  }
  glEnd();
}

void DrawRectangle(double x1, double y1, double x2, double y2) {
  glBegin(GL_QUADS);
  glVertex2d(x1, y1);
  glVertex2d(x2, y1);
  glVertex2d(x2, y2);
  glVertex2d(x1, y2);
  glEnd();
}

void DrawTriangle(double x1, double y1,
                  double x2, double y2,
                  double x3, double y3) {
  glBegin(GL_TRIANGLES);
  glVertex2d(x1, y1);
  glVertex2d(x2, y2);
  glVertex2d(x3, y3);
  glEnd();
}

void DrawText(double x, double y, char *string) {
  int len, i;
  void *font = GLUT_BITMAP_9_BY_15;

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glRasterPos2d(x, y);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }
  glDisable(GL_BLEND);
}


//
// GLUT callback functions
//

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  g_fractal->Draw();
  glutSwapBuffers();
}

void keyboard(unsigned char c, int x, int y) {
  switch (c) {
    case 27:  // esc
      exit(0);
      break;
    default:
      return;
  }
  glutPostRedisplay();
}

void reshape(int w, int h) {  // called when window's resized by user
  screen_x = w;
  screen_y = h;

  // set pixel resolution for final picture (screen coordinates)
  glViewport(0, 0, w, h);

  // set projection mode to 2D orthographic and set world coordinates
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, 0, h);
  glMatrixMode(GL_MODELVIEW);
}

void mouse(int mouse_button, int state, int x, int y) {
  if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    g_fractal->ZoomIn(x, screen_y - y);
  }
  if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP) {}
  if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
    g_fractal->Center(x, screen_y - y);
  }
  if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {}
  if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {}
  if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
    g_fractal->ZoomOut(x, screen_y - y);
  }
  glutPostRedisplay();
}

void InitializeMyStuff() {
  g_fractal = new Mandelbrot(screen_x, screen_y);
  g_fractal->Initialize();
}

int main(int argc, char **argv) {
  bool fullscreen = false;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(screen_x, screen_y);
  glutInitWindowPosition(50, 50);
  if (fullscreen) {
    glutGameModeString("800x600:32");
    glutEnterGameMode();
  } else {
    glutCreateWindow("Fractal");
  }
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glColor3d(0, 0, 0);        // foreground color
  glClearColor(1, 1, 1, 0);  // background color
  InitializeMyStuff();
  glutMainLoop();

  return 0;
}
