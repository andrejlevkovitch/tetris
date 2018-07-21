// tetris.cpp

#include "tetrishead.hpp"
#include <cstdbool>
#include <curses.h>
#include <tuple>
#include <vector>

Tetris::Tetris() : currentBrick_{}, score_{}, level_{}, lines_{} {
  screen_.resize(SIZE_Y, decltype(screen_)::value_type(SIZE_X, DEF_VALUE));
  Brick temp = currentBrick_;
}

Tetris::~Tetris() {}

void Tetris::frame() const {
  Koords temp{BEG_SCR};
  attron(COLOR_PAIR(FRAME_CELL));
  move_add(temp, ACS_ULCORNER);
  for (int i{}; i < screen_[0].size(); ++i) {
    addch(ACS_HLINE);
    addch(ACS_HLINE);
  }
  addch(ACS_URCORNER);
  Koords other_side{temp + Koords{0, SIZE_X * 2 + 1}};
  for (int i{}; i < screen_.size(); ++i) {
    move_add(temp.move_down(), ACS_VLINE);
    move_add(other_side.move_down(), ACS_VLINE);
  }
  move_add(temp.move_down(), ACS_LLCORNER);
  for (int i{}; i < screen_[0].size(); ++i) {
    addch(ACS_HLINE);
    addch(ACS_HLINE);
  }
  addch(ACS_LRCORNER);
  attroff(COLOR_PAIR(FRAME_CELL));
  refresh();
  return;
}

void Tetris::print_screen() const {
  Koords temp{BEG_SCR + Koords{0, 1}};
  for (const auto &i : screen_) {
    move_at(temp.move_down());
    for (const auto &j : i) {
      addch(j);
      addch(j);
    }
  }
  refresh();
  return;
}

void Tetris::print_level() const {
  move_at(SCORE);
  printw("SCORE: %u", score_);
  move_at(SCORE + Koords{1, 0});
  printw("LINES: %hu", lines_);
  move_at(SCORE + Koords{2, 0});
  printw("LEVEL: %hu", level_);
  refresh();
  return;
}

Rpair Tetris::game() {
  frame();
  print_screen();
  print_level();
  int ch{};
  bool endGame{false};
  auto start = std::chrono::system_clock::now();
  std::chrono::duration<int, std::milli> time_down{BEGIN_TIME_DOWN};
  do {
    currentBrick_.show();
    Brick next;
    bool needNewBreek{false};
    do {
      ch = 0;
      do {
        if (((std::chrono::system_clock::now() - start) > time_down)) {
          start = std::chrono::system_clock::now();
          ch = KEY_DOWN;
        } else {
          ch = input();
        }
      } while (!ch);
      switch (ch) {
      case 'k':
      case 'w':
      case KEY_UP:
        currentBrick_.rotade(screen_);
        break;
      case 'j':
      case 's':
      case KEY_DOWN:
        needNewBreek = currentBrick_.down(screen_);
        break;
      case 'h':
      case 'a':
      case KEY_LEFT:
        currentBrick_.left(screen_);
        break;
      case 'l':
      case 'd':
      case KEY_RIGHT:
        currentBrick_.right(screen_);
        break;
      case PAUSE:
        move_at(END_GAME_MESAGE);
        printw("...PAUSE...");
        refresh();
        getch();
        print_screen();
        currentBrick_.show();
        break;
      case '':
        ch = ESC;
        break;
      default:
        break;
      }
      if (needNewBreek) {
        try {
          intake();
        } catch (const char *) {
          endGame = true;
          ch = ESC;
        }
        break;
      }
    } while (ch != ESC);
    if (ch == ESC) {
      if (endGame) {
        move_at(END_GAME_MESAGE);
        printw("YOU LOSE...");
        move_at(END_GAME_MESAGE + Koords{1, 0});
        printw("Press ENTER");
        refresh();
        while (getch() != '\n')
          continue;
      }
    } else {
      auto count{delete_all_solutions()};
      switch (count) {
      case 1:
        score_ += ONE;
        break;
      case 2:
        score_ += TWO;
        break;
      case 3:
        score_ += TRI;
        break;
      case 4:
        score_ += TET;
        break;
      default:
        break;
      }
      if (count) {
        if (lines_ >= LINES_TO_NEW_LEVEL) {
          lines_ = 0;
          ++level_;
          time_down -= time_down / 8;
        }
        print_screen();
        print_level();
      }
      currentBrick_ = next;
    }
  } while (ch != ESC);
  clear();
  refresh();
  return Rpair{score_, level_};
}

unsigned short Tetris::delete_all_solutions() {
  unsigned short rezult{};
  for (int i{}; i < screen_.size(); ++i) {
    int counter{};
    for (int j{}; j < screen_[i].size(); ++j) {
      if (screen_[i][j] == DEF_VALUE) {
        break;
      } else {
        counter++;
      }
    }
    if (counter == screen_[i].size()) {
      ++lines_;
      ++rezult;
      screen_.erase(screen_.begin() + i);
      screen_.push_front(
          decltype(screen_)::value_type(screen_[i].size(), DEF_VALUE));
    }
  }
  return rezult;
}

void Tetris::intake() {
  auto temp{currentBrick_.sides().first};
  if (temp > BEG_SCR) {
    temp.to_index();
    auto block{currentBrick_.get_block()};
    for (int i = temp.getY(), l{}; l < block.size(); ++i, ++l) {
      for (int j = temp.getX(), m{}; m < block[l].size(); ++j, ++m) {
        if (block[l][m] != DEF_VALUE) {
          screen_[i][j] = block[l][m];
        }
      }
    }
    return;
  } else {
    throw "impassible, game over";
  }
}
