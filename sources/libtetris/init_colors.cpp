//init_colors.cpp

#include"../../include/tetrishead.hpp"
#include<curses.h>
#include<iostream>

int init_colors(void)
{
    if (!has_colors())
    {
        std::cout << "Colors are not supported!\n";
        return FALSE;
    }
    start_color();

    init_pair(FREE_CELL, COLOR_BLACK, COLOR_WHITE);
    init_pair(FRAME_CELL, COLOR_BLACK, COLOR_WHITE);
    init_pair(BRICK_CELL, COLOR_MAGENTA, COLOR_RED);

    return TRUE;
}
