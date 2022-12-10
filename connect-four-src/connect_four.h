#ifndef CONNECT_FOUR_H_
#define CONNECT_FOUR_H_

#include "graphics.h"

const int ROWS = 6;
const int COLS = 7;
const int NUM_SQUARES = ROWS * COLS;
const double SQUARE_SIZE = 75.0;
const double SQUARE_MARGIN = 5.0;
const double CIRCLE_RADIUS = SQUARE_SIZE / 2;
const double BOARD_MARGIN = 10.0;
const double BOARD_WIDTH = COLS * (SQUARE_SIZE + SQUARE_MARGIN * 2) +
               BOARD_MARGIN * 2;
const double BOARD_HEIGHT = ROWS * (SQUARE_SIZE + SQUARE_MARGIN * 2) +
               BOARD_MARGIN * 2;

enum {
  EMPTY,
  RED,
  BLACK,
  NOT_OVER,
  TIE
};

class ConnectFourBoard {
 public:
  ConnectFourBoard();
  void Initialize();
  int GameOver();
  int GetCurrentPlayer();
  void Draw();
  void HandleMouseClick(double x, double y);

private:
  int board_[COLS][ROWS];
  int player_;

  bool CheckForWin(int x, int y);
};

#endif  // CONNECT_FOUR_H_
