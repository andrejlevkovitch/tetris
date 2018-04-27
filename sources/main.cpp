//main.cpp

#include<curses.h>
#include"../include/tetrishead.hpp"
#include<cctype>

int main(int argc, char *argv[])
{
    initscr();
    keypad(stdscr, TRUE);
    noecho();

    if (!init_colors()) {
        return 1;
    }

    do {
        clear();
        Tetris game{};
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