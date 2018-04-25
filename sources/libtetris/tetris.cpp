//tetris.cpp

#include"../../include/tetrishead.hpp"
#include<curses.h>
#include<vector>
#include<cstdbool>

Tetris::Tetris()
{
    screen_.resize(SIZEY, std::remove_reference_t<decltype(screen_[0])> (SIZEX, DEF_VALUE));
}

Tetris::~Tetris()
{
}

void Tetris::frame() const
{
    Koords temp{BEGSCR};
    attron(COLOR_PAIR(FRAME_CELL));
    move_add(temp, ACS_ULCORNER);
    for (auto i : screen_[0]) {
        addch(ACS_HLINE);
        addch(ACS_HLINE);
    }
    addch(ACS_URCORNER);
    Koords other_side{temp, 0, SIZEX * 2 + 1};
    for (auto i : screen_) {
        move_add(temp.move_down(), ACS_VLINE);
        move_add(other_side.move_down(), ACS_VLINE);
    }
    move_add(temp.move_down(), ACS_LLCORNER);
    for (auto i : screen_[0]) {
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
    Koords temp{BEGSCR, 0, 1};
    for (auto i : screen_) {
        move_at(temp.move_down());
        for (auto j : i) {
            addch(j);
            addch(j);
        }
    }
    refresh();
    return;
}

void Tetris::game()
{
    frame();

    int ch{};
    Brick br;

    do {
        br.next();
        br.show();
        bool needNewBrick{};
        while ((ch = getch()) != ESC && !needNewBrick) {
            switch (ch) {
                case KEY_UP:
                    br.rotade();
                    break;
                case KEY_DOWN:
                    needNewBrick = br.down();
                    break;
                case KEY_LEFT:
                    br.left();
                    break;
                case KEY_RIGHT:
                    br.right();
                    break;
                default:
                    break;
            }
            Koords a;
            a = br;
            a.to_index();
            mvprintw(0, 0, "%2i\n%2i", a.getY(), a.getX());

            if (needNewBrick) {
                intake(br);
            }
        }
    } while (ch != ESC);

    return;
}

void Tetris::intake(const Brick &in)
{
    Koords temp;
    temp = in;
    temp.to_index();
    return;
}
