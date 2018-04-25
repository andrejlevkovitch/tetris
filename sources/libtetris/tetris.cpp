//tetris.cpp

#include"../../include/tetrishead.hpp"
#include<curses.h>
#include<vector>
#include<cstdbool>
#include<tuple>

Tetris::Tetris()
{
    screen_.resize(SIZEY, std::remove_reference_t<decltype(screen_[0])> (SIZEX, DEF_VALUE));
    {
        {
            Brick temp = current_;
        }
        current_ = Brick{};
    }
}

Tetris::~Tetris()
{
}

void Tetris::frame() const
{
    Koords temp{BEGSCR};
    attron(COLOR_PAIR(FRAME_CELL));
    move_add(temp, ACS_ULCORNER);
    for (int i{}; i < screen_[0].size(); ++i) {
        addch(ACS_HLINE);
        addch(ACS_HLINE);
    }
    addch(ACS_URCORNER);
    Koords other_side{temp + Koords{0, SIZEX * 2 + 1}};
    for (int i{}; i < screen_.size(); ++i) {
        move_add(temp.move_down(), ACS_VLINE);
        move_add(other_side.move_down(), ACS_VLINE);
    }
    move_add(temp.move_down(), ACS_LLCORNER);
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
    Koords temp{BEGSCR + Koords{0, 1}};
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
    do {
        current_.show();
        Brick next{};
        bool needNewBrick{false};
        while ((ch = getch()) != ESC) {
            switch (ch) {
                case KEY_UP:
                    current_.rotade(screen_);
                    break;
                case KEY_DOWN:
                    needNewBrick = current_.down(screen_);
                    break;
                case KEY_LEFT:
                    current_.left(screen_);
                    break;
                case KEY_RIGHT:
                    current_.right(screen_);
                    break;
                default:
                    break;
            }
            if (needNewBrick) {
                intake(current_);
                break;
            }
        }
        if (delete_all_solutions()) {
            frame();
        }
        current_ = next;
    } while (ch != ESC);
    return;
}

bool Tetris::delete_all_solutions()
{
    bool rezult{false};
    for (int i{}; i < screen_.size(); ++i) {
        int counter{};
        for (int j{}; j < screen_[i].size(); ++ j) {
            if (screen_[i][j] == DEF_VALUE) {
                break;
            }
            else {
                counter++;
            }
        }
        if (counter == screen_[i].size()) {
            rezult = true;
            screen_.erase(screen_.begin() + i);
            screen_.insert(screen_.begin(), std::remove_reference_t<decltype(screen_[i])>(screen_[i].size(), DEF_VALUE));
        }
    }
    return rezult;
}

void Tetris::intake(const Brick &in)
{
    auto temp{in.sides().first};
    temp.to_index();
    auto block{in.get_block()};
    for (int i = temp.getY(), l{}; l < block.size(); ++i, ++l) {
        for (int j = temp.getX(), m{}; m < block[l].size(); ++j, ++m) {
            if (block[l][m] != DEF_VALUE) {
                screen_[i][j] = block[l][m];
            }
        }
    }
    return;
}
