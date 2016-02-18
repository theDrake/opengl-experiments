#include "ConnectFour.h"

ConnectFourBoard::ConnectFourBoard() {
  Initialize();
}

void ConnectFourBoard::Initialize() {
  for (int i = 0; i < COLS; ++i) {
    for (int j = 0; j < ROWS; ++j) {
      board_[i][j] = EMPTY;
    }
  }
  player_ = RED;
}

int ConnectFourBoard::GameOver() {
  int emptySquares = 0;

  for (int i = 0; i < COLS; ++i) {
    for (int j = 0; j < ROWS; ++j) {
      if (board_[i][j] == EMPTY) {
        emptySquares++;
      } else {
        if (CheckForWin(i, j)) {
          return board_[i][j];  // Returns the winner's color: RED or BLACK.
        }
      }
    }
  }

  if (emptySquares == 0) {
    return TIE;
  }

  return NOT_OVER;
}

// Checks a limited number of possible win combinations for a given set of
// coordinates. Multiple sets of coordinates must be passed to this method in
// order to thoroughly check for a win.
bool ConnectFourBoard::CheckForWin(int x, int y) {
  int i, j;

  // Check for a horizontal win:
  for (i = x; i < x + 4 && i < COLS; ++i) {
    if (board_[i][y] != board_[x][y]) {
      break;
    }
  }
  if (i == x + 4) {
    return true;
  }

  // Check for a vertical win:
  for (i = y; i < y + 4 && i < ROWS; ++i) {
    if (board_[x][i] != board_[x][y]) {
      break;
    }
  }
  if (i == y + 4) {
    return true;
  }

  // Check for a diagonal win:
  for (i = x, j = y;
       i < x + 4 && i < COLS && j < y + 4 && j < ROWS;
       ++i, ++j) {
    if (board_[i][j] != board_[x][y]) {
      break;
    }
  }
  if (i == x + 4 && j == y + 4) {
    return true;
  }
  for (i = x, j = y;
       i > x - 4 && i > 0 && j < y + 4 && j < ROWS;
       --i, ++j) {
    if (board_[i][j] != board_[x][y]) {
      break;
    }
  }
  if (i == x - 4 && j == y + 4) {
    return true;
  }

  return false;
}

void ConnectFourBoard::Draw() {
  double x1, y1, x2, y2;

  // Black boundary:
  glColor3d(0, 0, 0);
  DrawRectangle(0, 0, BOARD_WIDTH, BOARD_HEIGHT);

  // Draw each square, including contents (if any):
  for (int i = 0; i < COLS; ++i) {
    for (int j = 0; j < ROWS; ++j) {
      x1 = BOARD_MARGIN + i * (SQUARE_SIZE + SQUARE_MARGIN * 2);
      y1 = BOARD_MARGIN + j * (SQUARE_SIZE + SQUARE_MARGIN * 2);
      x2 = BOARD_MARGIN + (i + 1) * (SQUARE_SIZE + SQUARE_MARGIN * 2);
      y2 = BOARD_MARGIN + (j + 1) * (SQUARE_SIZE + SQUARE_MARGIN * 2);
      glColor3d(0, 0, 0);
      DrawRectangle(x1, y1, x2, y2);
      glColor3d(1, 1, 1);
      DrawRectangle(x1 + SQUARE_MARGIN, y1 + SQUARE_MARGIN, x2 - SQUARE_MARGIN, y2 - SQUARE_MARGIN);
      if (board_[i][j] != EMPTY) {
        if (board_[i][j] == RED) {
          glColor3d(1, 0, 0);
        } else {
          glColor3d(0, 0, 0);
        }
        DrawCircle((x1 + x2) / 2, (y1 + y2) / 2, CIRCLE_RADIUS);
      }
    }
  }

  // Print an appropriate message:
  char msg[STR_LEN + 1];
  switch(GameOver()) {
    case RED:
      strcpy(msg, "Red wins!");
      break;
    case BLACK:
      strcpy(msg, "Black wins!");
      break;
    case TIE:
      strcpy(msg, "It's a tie!");
      break;
    default:  // The game isn't over yet.
      if (player_ == RED) {
        strcpy(msg, "Red's turn.");
      } else {
        strcpy(msg, "Black's turn.");
      }
      break;
  }
  glColor3d(0, 0, 0);
  DrawText(BOARD_MARGIN, BOARD_HEIGHT + BOARD_MARGIN, msg);
}

void ConnectFourBoard::HandleMouseClick(double x, double y) {
  int i, j;
  double columnSize;

  if (GameOver() != NOT_OVER) {
    return;
  }

  columnSize = SQUARE_SIZE + 2 * SQUARE_MARGIN;
  for (i = 0; i < COLS; ++i) {
    if (x > BOARD_MARGIN + i * columnSize &&
        x < BOARD_MARGIN + (i + 1) * columnSize) {
      // Search for an open row in the clicked column:
      j = 0;
      while (board_[i][j] != EMPTY && j < ROWS) {
        ++j;
      }
      if (j < ROWS) {
        board_[i][j] = player_;
        if (player_ == RED) {
          player_ = BLACK;
        } else {
          player_ = RED;
        }
      }
    }
  }
}
