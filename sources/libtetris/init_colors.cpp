// init_colors.cpp

#include "tetrishead.hpp"
#include <curses.h>

void init_colors(void) {
  if (!has_colors()) {
    throw "Colors are not supported!";
  }
  start_color();

  init_pair(FREE_CELL, COLOR_WHITE, COLOR_WHITE);
  init_pair(FRAME_CELL, COLOR_BLACK, COLOR_WHITE);
  init_pair(BRICK_R_CELL, COLOR_RED, COLOR_RED);
  init_pair(BRICK_G_CELL, COLOR_GREEN, COLOR_GREEN);
  init_pair(BRICK_Y_CELL, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(BRICK_M_CELL, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(BRICK_C_CELL, COLOR_CYAN, COLOR_CYAN);
  init_pair(BRICK_B_CELL, COLOR_BLUE, COLOR_BLUE);

  return;
}
