//brick.cpp

#include"../../include/tetrishead.hpp"
#include<vector>
#include<curses.h>
#include<tuple>
#include<cstdbool>
#include<cstdlib>
#include<ctime>

Brick::Brick() : direction_{RIGHT}, position_{SHOW_POSITION}, center_{DEF_CENTRUM}
{
    BrickType figure{};
    {
        srand(time(NULL));
        figure = static_cast<BrickType>(rand() % N_BRICK_KIND);
        name_ = figure;
    }

    {
        block_ = BLOCKS[rand() % BLOCKS.size()];
    }
    switch(figure) {
        case BRICK_I:
            field_.resize(1, std::remove_reference_t<decltype(field_[0])> (4, DEF_VALUE));
            for (int i{}; i < field_[0].size(); ++i) {
                field_[0][i] = block_;
            }
            break;
        case BRICK_J:
            field_.resize(2, std::remove_reference_t<decltype(field_[0])> (3, DEF_VALUE));
            field_[1][2] = block_;
            for (int i{}; i < field_[0].size(); ++i) {
                field_[0][i] = block_;
            }
            break;
        case BRICK_L:
            field_.resize(2, std::remove_reference_t<decltype(field_[0])> (3, DEF_VALUE));
            field_[1][0] = block_;
            for (int i{}; i < field_[0].size(); ++i) {
                field_[0][i] = block_;
            }
            break;
        case BRICK_O:
            field_.resize(2, std::remove_reference_t<decltype(field_[0])> (2, block_));
            break;
        case BRICK_S:
            field_.resize(2, std::remove_reference_t<decltype(field_[0])> (3, DEF_VALUE));
            for (int i{}; i < field_.size(); ++i) {
                for (int j{1 - i}; j + i < field_[i].size(); ++j) {
                    field_[i][j] = block_;
                }
            }
            break;
        case BRICK_T:
            field_.resize(2, std::remove_reference_t<decltype(field_[0])> (3, DEF_VALUE));
            field_[0][1] = block_;
            for (int i{}; i < field_[1].size(); ++i) {
                field_[1][i] = block_;
            }
            break;
        case BRICK_Z:
            field_.resize(2, std::remove_reference_t<decltype(field_[0])> (3, DEF_VALUE));
            for (int i{}; i < field_.size(); ++i) {
                for (int j{i}; j - i < field_[i].size() - 1; ++j) {
                    field_[i][j] = block_;
                }
            }
            break;
        default:
            break;
    }

    {
        auto count_of_rotedes{rand() % 4};
        for (int i{}; i < count_of_rotedes; ++i) {
            rotor();
        }
    }
    beg_direction_ = direction_;
    show();
    position_ = IN_POSITION;
}

Brick::~Brick()
{
    while (direction_ != beg_direction_) {
        rotor();
    }
    position_ = SHOW_POSITION;
    show(' ');
}

const Brick &Brick::show(chtype block) const
{
    Koords stat{sides().first};
    Koords temp{stat};
    if (block == BLOCKS[0]) {
        block = block_;
    }
    for (const auto &i : field_) {
        temp = stat;
        for (const auto &j : i) {
            if (j != DEF_VALUE && temp > BEG_SCR) {
                move_at(temp);
                addch(block);
                addch(block);
            }
            temp.move_right();
        }
        stat.move_down();
    }
    move_at(SHOW_POSITION);
    refresh();
    return *this;
}

bool Brick::is_pasible(Field &out) const
{
    auto temp{sides().first};
    temp.to_index();
    for (int i{}, l = temp.getY(); i < field_.size(); ++i, ++l) {
        for (int j{}, m = temp.getX(); j < field_[i].size(); ++j, ++m) {
            if (l >= 0 && m >= 0 && field_[i][j] != DEF_VALUE && out[l][m] != DEF_VALUE) {
                return false;
            }
        }
    }
    return true;
}

Brick &Brick::rotade(Field &out)
{
    if (name_ == BRICK_O) {
        return *this;
    }
    show(DEF_VALUE);
    {
        auto spare{position_};
        rotor();
        int counter{};
        bool need_cikle = false;
        do {
            while (!(sides().first > Koords{BEG_SCR - BUFFER_PLACE})) {
                position_.move_right();
            }
            while (!(sides().second < Koords{END_SCR + BUFFER_PLACE})) {
                position_.move_left();
            }
            while (!(sides().second < END_SCR)) {
                position_.move_up();
            }
            if (!is_pasible(out)) {
                position_ = spare;
                need_cikle = true;
                counter++;
                switch (counter) {
                    case 0:
                        position_.move_left();
                        break;
                    case 1:
                        position_.move_right();
                        break;
                    default:
                        need_cikle = false;
                        for (int i{}; i < 3; ++i) {
                            rotor();
                        }
                        break;
                }
            }
            else {
                need_cikle = false;
            }
        } while(need_cikle);
    }
    show();
    return *this;
}

bool Brick::down(Field &out)
{
    bool returnVal{false};
    show(DEF_VALUE);
    auto spare{position_};
    position_.move_down();
    if (sides().second < END_SCR && is_pasible(out)) {
    }
    else {
        position_ = spare;
        returnVal = true;
    }
    show();
    return returnVal;
}

void Brick::right(Field &out)
{
    show(DEF_VALUE);
    auto spare{position_};
    position_.move_right();
    if (sides().second < END_SCR && is_pasible(out)) {
    }
    else {
        position_ = spare;
    }
    show();
    return;
}

void Brick::left(Field &out)
{
    show(DEF_VALUE);
    auto spare{position_};
    position_.move_left();
    if (sides().first > Koords{BEG_SCR - BUFFER_PLACE} && is_pasible(out)) {
    }
    else {
        position_ = spare;
    }
    show();
    return;
}

std::pair<Koords, Koords> Brick::sides() const
{
    Koords a{position_ - Koords{center_ + Koords{0, center_.getX()}}};
    Koords b{a + Koords(field_.size() - 1, field_[0].size() * 2 - 1)};
    return std::pair<Koords, Koords>(a, b);
}

const Koords &Brick::get_koords() const
{
    return position_;
}

Brick &Brick::rotor()
{
    Field temp(field_[0].size(), std::remove_reference_t<decltype(field_[0])> (field_.size(), DEF_VALUE));
    bool no_uptade_center{true};
    for (int i{}; i < field_.size(); ++i) {
        for (int j{}; j < field_[i].size(); ++j) {
            int n = field_.size() - i - 1;
            temp[j][n] = field_[i][j];
            if (center_ == Koords(i, j) && no_uptade_center) {
                center_ = Koords(j, n);
                no_uptade_center = false;
            }
        }
    }
    direction_++;
    field_ = temp;
    return *this;
}

Field Brick::get_block() const
{
    return field_;
}
