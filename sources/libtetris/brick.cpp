//brick.cpp

#include"../../include/tetrishead.hpp"
#include<vector>
#include<curses.h>

Brick::Brick(const BrickType figure) : direction_(RIGHT), position_(INPUTBRICKY, INPUTBRICKX)
{
    switch(figure) {
        case BRICK_I:
            field_.resize(1, std::remove_reference_t<decltype(field_[0])> (4, DEF_VALUE));
            for (int i{}; i < field_[0].size(); ++i) {
                field_[0][i] = BLOCK;
            }
            break;
        case BRICK_J:
            field_.resize(2, std::remove_reference_t<decltype(field_[0])> (3, DEF_VALUE));
            field_[0][0] = BLOCK;
            for (int i{}; i < field_[1].size(); ++i) {
                field_[1][i] = BLOCK;
            }
            break;
        case BRICK_L:
            field_.resize(2, std::remove_reference_t<decltype(field_[0])> (3, DEF_VALUE));
            field_[0][field_[0].size() - 1] = BLOCK;
            for (int i{}; i < field_[1].size(); ++i) {
                field_[1][i] = BLOCK;
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

void Brick::show() const
{
    int y{position_.getY()}, x{position_.getX()};
    int a{}, b{};
    for (int i{}; i < field_.size(); ++i) {
        move(y++, x);
        refresh();
        for (int j{}; j < field_[i].size(); ++j) {
            if (field_[i][j] != DEF_VALUE) {
                addch(field_[i][j]);
                addch(field_[i][j]);
            }
            else {
                getyx(curscr, a, b);
                move(a, b + 2);
            }
            refresh();
        }
    }

    return;
}

void Brick::rotade()
{
    auto a{static_cast<int>(direction_) + 1};
    direction_ = (a > 3) ? RIGHT : static_cast<Direction>(a);
    return;
}
