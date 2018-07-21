// main.cpp

#include "tetrishead.hpp"
#include <cctype>
#include <curses.h>
#include <iostream>

int main(int argc, char *argv[]) {
  initscr();
  keypad(stdscr, TRUE);
  noecho();
  leaveok(stdscr, TRUE);

  try {
    init_colors();
  } catch (const char *error) {
    endwin();
    std::cerr << error << std::endl;
    std::exit(1);
  }

  do {
    clear();
    Tetris game;
    save_rezult(game.game());
    move(0, 0);
    printw("Do you want play again? (y/n)\n");
    show_record_table();
    refresh();
  } while (toupper(getch()) == 'Y');

  clear();
  refresh();
  endwin();

  return 0;
}
