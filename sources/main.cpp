//main.cpp

#include<iostream>
#include<curses.h>
#include"../include/tetrishead.hpp"
#include<unistd.h>

int main(int argc, char *argv[])
{
    initscr();

    if (!init_colors()) {
        return 1;
    }

//  Tetris game{};
//  game.game();
//  Brick b{BRICK_T};
//  b.show();

    for (int i{}; i < 7; ++i) {
        Brick b{static_cast<BrickType>(i)};
        b.show();
        refresh();
        sleep(1);
        clear();
    }
    noecho();
    getch();

    endwin();

    return 0;
}
