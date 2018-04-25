//brick.cpp

#include"../../include/tetrishead.hpp"
#include<vector>
#include<curses.h>
#include<random>
#include<chrono>
#include<tuple>

Brick::Brick(const BrickType &figure) : direction_(RIGHT), position_(INPOSITION)
{
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(0, 3);
    direction_ = static_cast<Direction>(distribution(generator));
    switch(figure) {
        case BRICK_I:
            field_.resize(1, std::remove_reference_t<decltype(field_[0])> (4, DEF_VALUE));
            for (int i{}; i < field_[0].size(); ++i) {
                field_[0][i] = BLOCK;
            }
            break;
        case BRICK_J:
            field_.resize(2, std::remove_reference_t<decltype(field_[0])> (3, DEF_VALUE));
            field_[1][2] = BLOCK;
            for (int i{}; i < field_[0].size(); ++i) {
                field_[0][i] = BLOCK;
            }
            break;
        case BRICK_L:
            field_.resize(2, std::remove_reference_t<decltype(field_[0])> (3, DEF_VALUE));
            field_[1][0] = BLOCK;
            for (int i{}; i < field_[0].size(); ++i) {
                field_[0][i] = BLOCK;
            }
            break;
        case BRICK_O:
            field_.resize(2, std::remove_reference_t<decltype(field_[0])> (2, BLOCK));
            break;
        case BRICK_S:
            field_.resize(2, std::remove_reference_t<decltype(field_[0])> (3, DEF_VALUE));
            for (int i{}; i < field_.size(); ++i) {
                for (int j{1 - i}; j + i < field_[i].size(); ++j) {
                    field_[i][j] = BLOCK;
                }
            }
            break;
        case BRICK_T:
            field_.resize(2, std::remove_reference_t<decltype(field_[0])> (3, DEF_VALUE));
            field_[0][1] = BLOCK;
            for (int i{}; i < field_[1].size(); ++i) {
                field_[1][i] = BLOCK;
            }
            break;
        case BRICK_Z:
            field_.resize(2, std::remove_reference_t<decltype(field_[0])> (3, DEF_VALUE));
            for (int i{}; i < field_.size(); ++i) {
                for (int j{i}; j - i < field_[i].size() - 1; ++j) {
                    field_[i][j] = BLOCK;
                }
            }
            break;
        default:
            break;
    }
}

Brick::~Brick()
{
}

const Brick &Brick::show(const chtype block) const
{
    Koords stat{position_};
    Koords temp{position_};
    switch (direction_) {
        case RIGHT:
            stat.move_left();
            for (auto i : field_) {
                temp = stat;
                for (auto j : i) {
                    if (j != DEF_VALUE && temp > BEGSCR) {
                        move_at(temp);
                        addch(block);
                        addch(block);
                    }
                    temp.move_right();
                }
                stat.move_down();
            }
            break;
        case LEFT:
            stat.move_right();
            for (auto i : field_) {
                temp = stat;
                for (auto j : i) {
                    if (j != DEF_VALUE && temp > BEGSCR) {
                        move_at(temp);
                        addch(block);
                        addch(block);
                    }
                    temp.move_left();
                }
                stat.move_up();
            }
            break;
        case UP:
            stat.move_down();
            for (auto i : field_) {
                temp = stat;
                for (auto j : i) {
                    if (j != DEF_VALUE && temp > BEGSCR) {
                        move_at(temp);
                        addch(block);
                        addch(block);
                    }
                    temp.move_up();
                }
                stat.move_right();
            }
            break;
        case DOWN:
            stat.move_up();
            for (auto i : field_) {
                temp = stat;
                for (auto j : i) {
                    if (j != DEF_VALUE && temp > BEGSCR) {
                        move_at(temp);
                        addch(block);
                        addch(block);
                    }
                    temp.move_down();
                }
                stat.move_left();
            }
            break;
        default:
            break;
    }

    return *this;
}

Brick &Brick::rotade()
{
    if (field_[0].size() == 2) {
        return *this;
    }
    clean();
    auto a{direction_ + 1};
    direction_ = (a > 3) ? RIGHT : static_cast<Direction>(a);
    while (!(sides().first > BEGSCR)) {
        position_.move_right();
    }
    Koords temp{ENDSCR, 2, 0};
    while (!(sides().second < temp)) {
        position_.move_left();
    }
    while (!(sides().second < ENDSCR)) {
        position_.move_up();
    }
    show();
    return *this;
}

bool Brick::down()
{
    if (sides().second.move_down() < ENDSCR) {
        clean();
        position_.move_down();
        show();
    }
    else {
        return true;
    }
    return false;
}

Brick &Brick::right()
{
    if (sides().second.move_right() < ENDSCR) {
        clean();
        position_.move_right();
        show();
    }
    return *this;
}

Brick &Brick::left()
{
    if (sides().first.move_left() > BEGSCR) {
        clean();
        position_.move_left();
        show();
    }
    return *this;
}

std::pair<Koords, Koords> Brick::sides() const
{
    int a{}, b{}, c{}, d{};
    switch (direction_) {
        case RIGHT:
            a = - 2;
            b = (field_[0].size() - 1) * 2 - 1;
            c = 0;
            d = field_.size() - 1;
            break;
        case LEFT:
            a = - ((field_[0].size() - 2) * 2);
            b = 3;
            c = field_.size() - 1;
            d = 0;
            break;
        case UP:
            a = 0;
            b = (field_.size()) * 2 - 1;
            c = field_[0].size() - 2;
            d = 1;
            break;
        case DOWN:
            a = - (field_.size() - 1) * 2;
            b = 1;
            c = 1;
            d = field_[0].size() - 2;
            break;
    }
    return std::pair<Koords, Koords>(Koords{position_, c, a}, Koords{position_, d, b});
}

const Brick &Brick::clean() const
{
    show(DEF_VALUE);
    return *this;
}

Brick &Brick::next()
{
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(0, NBrTy - 1);
    *this = Brick{static_cast<BrickType>(distribution(generator))};
    return *this;
}

const Koords &Brick::get_koords() const
{
    return position_;
}
