//move_at.cpp

#include"../../include/tetrishead.hpp"
#include<curses.h>

void move_at(const Koords &in)
{
    move(in.getY(), in.getX());
    return;
}

void move_add(const Koords &in, chtype symbol)
{
    move_at(in);
    addch(symbol);
    return;
}

Direction &operator++(Direction &dir, int)
{
    auto a{static_cast<int>(dir)};
    return dir = (++a > 3) ? RIGHT : static_cast<Direction>(a);
}
