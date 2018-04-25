//main.cpp

#include<curses.h>
#include"../include/tetrishead.hpp"

int main(int argc, char *argv[])
{
    initscr();
    keypad(stdscr, TRUE);
    noecho();

    if (!init_colors()) {
        return 1;
    }

    Tetris game{};
    game.game();

    endwin();

    return 0;
}
