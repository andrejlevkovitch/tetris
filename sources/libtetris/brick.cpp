//brick.cpp

#include"../../include/tetrishead.hpp"
#include<vector>
#include<curses.h>
#include<random>
#include<chrono>
#include<tuple>
#include<cstdbool>

Brick::Brick() : direction_(RIGHT), position_(SHOWPOSITION), center_(DEFCENTER)
{
    BrickType figure{};
    {
        std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> distribution(0, NBrTy - 1);
        figure = static_cast<BrickType>(distribution(generator));
        name_ = figure;
    }

    {
        std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> distribution(0, BLOCKS.size() - 1);
        block_ = BLOCKS[distribution(generator)];
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
        std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> distribution(0, 3);
        auto count_of_rotedes{(distribution(generator))};
        for (int i{}; i < count_of_rotedes; ++i) {
            rotor();
        }
    }
    beg_direction_ = direction_;
    show();
    position_ = INPOSITION;
}

Brick::~Brick()
{
    while (direction_ != beg_direction_) {
        rotor();
    }
    position_ = SHOWPOSITION;
    show(' ');
}

const Brick &Brick::show(chtype block) const
{
    Koords stat{sides().first};
    Koords temp{stat};
    if (block == BLOCKS[0]) {
        block = block_;
    }
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
    return *this;
}

bool Brick::is_pasible(Field &out) const
{
    auto temp{sides().first};
    temp.to_index();
    for (int i{}, l = temp.getY(); i < field_.size(); ++i, ++l) {
        for (int j{}, m = temp.getX(); j < field_[i].size(); ++j, ++m) {
            if (field_[i][j] != DEF_VALUE && out[l][m] != DEF_VALUE) {
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
    clean();
    {
        auto spare{position_};
        rotor();
        int counter{};
        bool need_cikle = false;
        do {
            refresh();
            while (!(sides().first > BEGSCR)) {
                position_.move_right();
            }
            while (!(sides().second < Koords{ENDSCR + Koords{2, 0}})) {
                position_.move_left();
            }
            while (!(sides().second < ENDSCR)) {
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
            refresh();
        } while(need_cikle);
    }
    show();
    return *this;
}

bool Brick::down(Field &out)
{
    bool returnVal{false};
    clean();
    auto spare{position_};
    position_.move_down();
    if (sides().second < ENDSCR && is_pasible(out)) {
    }
    else {
        position_ = spare;
        returnVal = true;
    }
    show();
    return returnVal;
}

Brick &Brick::right(Field &out)
{
    clean();
    auto spare{position_};
    position_.move_right();
    if (sides().second < ENDSCR && is_pasible(out)) {
    }
    else {
        position_ = spare;
    }
    show();
    return *this;
}

Brick &Brick::left(Field &out)
{
    clean();
    auto spare{position_};
    position_.move_left();
    if (sides().first > BEGSCR && is_pasible(out)) {
    }
    else {
        position_ = spare;
    }
    show();
    return *this;
}

std::pair<Koords, Koords> Brick::sides() const
{
    Koords a{position_ - Koords{center_ + Koords{0, center_.getX()}}};
    Koords b{a + Koords{field_.size() - 1, field_[0].size() * 2 - 1}};
    return std::pair<Koords, Koords>(a, b);
}

const Brick &Brick::clean() const
{
    show(DEF_VALUE);
    return *this;
}

const Koords &Brick::get_koords() const
{
    return position_;
}

Brick &Brick::rotor()
{
    decltype(field_) temp(field_[0].size(), std::remove_reference_t<decltype(field_[0])> (field_.size(), DEF_VALUE));
    bool no_uptade_center{true};
    for (unsigned i{}; i < field_.size(); ++i) {
        for (unsigned j{}; j < field_[i].size(); ++j) {
            unsigned n = field_.size() - i - 1;
            temp[j][n] = field_[i][j];
            if (center_ == Koords{i, j} && no_uptade_center) {
                center_ = Koords{j, n};
                no_uptade_center = false;
            }
        }
    }
    direction_++;
    field_ = temp;
    refresh();
    return *this;
}

Field Brick::get_block() const
{
    return field_;
}
