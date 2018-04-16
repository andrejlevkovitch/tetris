//move_at.cpp

#include"../../include/tetrishead.hpp"
#include<curses.h>

void move_at(const Koords &in)
{
    move(in.getY(), in.getX());
    return;
}
