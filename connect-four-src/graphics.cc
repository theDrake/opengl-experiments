#include "graphics.h"

double gScreenX = 900;
double gScreenY = 600;
ConnectFourBoard gBoard;

//
// Functions that draw basic primitives:
//

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

void DrawCircle(double x1, double y1, double radius) {
  glBegin(GL_POLYGON);
  for (int i = 0; i < CURVE_RESOLUTION; i++) {
    double theta = (double) i / CURVE_RESOLUTION * 2.0 * PI;
    double x = x1 + radius * cos(theta);
    double y = y1 + radius * sin(theta);
    glVertex2d(x, y);
  }
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
// GLUT callback functions:
//

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  gBoard.Draw();
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

void reshape(int w, int h) {
  gScreenX = w;
  gScreenY = h;

  // set pixel resolution of final picture (screen coordinates)
  glViewport(0, 0, w, h);

  // set projection mode to 2D orthographic and set world coordinates
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, 0, h);
  glMatrixMode(GL_MODELVIEW);
}

void mouse(int mouseButton, int state, int x, int y) {
  y = gScreenY - y;

  if (mouseButton == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    gBoard.HandleMouseClick(x, y);
  }
  if (mouseButton == GLUT_LEFT_BUTTON && state == GLUT_UP) {}
  if (mouseButton == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {}
  if (mouseButton == GLUT_RIGHT_BUTTON && state == GLUT_UP) {}
  if (mouseButton == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {}
  if (mouseButton == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {}
  glutPostRedisplay();
}

int main(int argc, char **argv) {
  bool fullscreen = false;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(gScreenX, gScreenY);
  glutInitWindowPosition(50, 50);
  if (fullscreen) {
    glutGameModeString("800x600:32");
    glutEnterGameMode();
  } else {
    glutCreateWindow("Connect Four!");
  }
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glClearColor(1, 1, 1, 0);  // background color
  gBoard.Initialize();
  glutMainLoop();

  return 0;
}
