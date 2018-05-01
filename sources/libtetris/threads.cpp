//threads.cpp

#include"../../include/tetrishead.hpp"
#include<curses.h>
#include<sys/select.h>
#include<thread>
#include<chrono>

int input()
{
    fd_set rfds;
    struct timeval tv;
    int retval;
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    tv.tv_sec = 0;
    tv.tv_usec = 100;
    retval = select(1, &rfds, NULL, NULL, &tv);
    if (retval)
        return getch();
    else
        return 0;
}

void endless(const bool &exitParametr, int &defoltMotion, unsigned short &level)
{
    bool to_exit {};
    unsigned short time {BEGIN_TIME_DOWN};
    unsigned short copy_level {};
    do {
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
        threadMutex.lock();
        if (level != copy_level) {
            copy_level = level;
            time -= time / 10;
        }
        defoltMotion = KEY_DOWN;
        to_exit = exitParametr;
        threadMutex.unlock();
    } while (!to_exit);
}
