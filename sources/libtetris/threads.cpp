//threads.cpp

#include"tetrishead.hpp"
#include<curses.h>

int input()
{
    wtimeout(curscr, 100);
    int in = wgetch(curscr);
    if (in == ESC) {
        int a = wgetch(curscr);
        if (a != ERR) {
            int b = wgetch(curscr);
            if (a == 91) {
                switch (b) {
                    case 65:
                        in = KEY_UP;
                        break;
                    case 66:
                        in = KEY_DOWN;
                        break;
                    case 68:
                        in = KEY_LEFT;
                        break;
                    case 67:
                        in = KEY_RIGHT;
                        break;
                    default:
                        in = 0;
                        break;
                }
            }
        }
    }
    wtimeout(curscr, - 1);
    return (in == ERR) ? 0 : in;
}
