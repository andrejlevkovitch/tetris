//tetris.cpp

#include"../../include/tetrishead.hpp"
#include<curses.h>
#include<vector>

Tetris::Tetris() : beginen_(BYSCREEN, BXSCREEN)
{
    screen_.resize(SIZEY, std::remove_reference_t<decltype(screen_[0])> (SIZEX, DEF_VALUE));
    field_ = screen_;

    {
        int ey{}, ex{};
        ey = beginen_.getY() + screen_.size() + 1;
        ex = beginen_.getX() + screen_[0].size() + screen_[0].size() + 1;
        end_ = Koords{ey, ex};
    }
}

Tetris::~Tetris()
{
}

void Tetris::frame() const
{
    int y{beginen_.getY()}, x{beginen_.getX()};
    attron(COLOR_PAIR(FRAME_CELL));
    mvaddch(y, x, ACS_ULCORNER);
    for (int i{}; i < screen_[0].size(); ++i) {
        addch(ACS_HLINE);
        addch(ACS_HLINE);
    }
    addch(ACS_URCORNER);
    y++;
    for (int i{}; i < screen_.size(); ++i, y = ++y) {
        mvaddch(y, x, ACS_VLINE);
        mvaddch(y, end_.getX(), ACS_VLINE);
    }
    mvaddch(y, x, ACS_LLCORNER);
    for (int i{}; i < screen_[0].size(); ++i) {
        addch(ACS_HLINE);
        addch(ACS_HLINE);
    }
    addch(ACS_LRCORNER);
    attroff(COLOR_PAIR(FRAME_CELL));

    print_screen();
    return;
}

void Tetris::print_screen() const
{
    for (int i{}; i < screen_.size(); ++i) {
        move(beginen_.getY() + i + 1, beginen_.getX() + 1);
        for (int j{}; j < screen_[i].size(); ++j) {
            addch(screen_[i][j]);
            addch(screen_[i][j]);
        }
    }
    refresh();
    return;
}

void Tetris::game()
{
    frame();
    return;
}
