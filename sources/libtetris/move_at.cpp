// move_at.cpp

#include "tetrishead.hpp"
#include <curses.h>

void move_at(const Koords &in) {
  move(in.getY(), in.getX());
  return;
}

void move_add(const Koords &in, chtype symbol) {
  move_at(in);
  addch(symbol);
  return;
}
