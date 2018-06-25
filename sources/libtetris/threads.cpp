//threads.cpp

#include"tetrishead.hpp"
#include<curses.h>
#include<thread>
#include<chrono>
#include<atomic>

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

void endless(const std::atomic<bool> &exitParametr, std::atomic<int> &defoltMotion, std::atomic<int> &level)
{
    std::chrono::milliseconds time {BEGIN_TIME_DOWN};
    unsigned short copy_level {};
    do {
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
        if (level.load() != copy_level) {
            copy_level = level.load();
            time -= time / 10;
        }
        defoltMotion.store(KEY_DOWN);
    } while (!exitParametr.load());
}
