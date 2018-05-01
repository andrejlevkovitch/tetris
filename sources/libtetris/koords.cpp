//cords.cpp

#include"../../include/tetrishead.hpp"
#include<cstdbool>

Koords::Koords (short y, short x) : y_(y), x_(x)
{
}

Koords::Koords(const Koords &in) : y_(in.y_), x_(in.x_)
{
}

auto Koords::getY() const -> decltype(y_)
{
    return y_;
}

auto Koords::getX() const -> decltype(x_)
{
    return x_;
}

bool Koords::operator<(const Koords &right) const
{
    if (y_ < right.y_ && x_ < right.x_)
        return true;
    else
        return false;
}

bool Koords::operator>(const Koords &right) const
{
    if (y_ > right.y_ && x_ > right.x_)
        return true;
    else
        return false;
}

Koords &Koords::move_right()
{
    x_ += PAS_SIDE;
    return *this;
}

Koords &Koords::move_left()
{
    x_ -= PAS_SIDE;
    return *this;
}

Koords &Koords::move_up()
{
    y_ -= PAS_FRWD;
    return *this;
}

Koords &Koords::move_down()
{
    y_ += PAS_FRWD;
    return *this;
}

Koords &Koords::to_index()
{
    *this = *this - BEG_SCR - Koords {1, 1};
    *this = Koords (y_, x_ / 2);
    return *this;
}

Koords Koords::operator-(const Koords &right) const
{
    return Koords (y_ - right.y_, x_ - right.x_);
}

Koords Koords::operator+(const Koords &right) const
{
    return Koords (y_ + right.y_, x_ + right.x_);
}

bool Koords::operator==(const Koords &right) const
{
    if (y_ == right.y_ && x_ == right.x_)
        return true;
    else
        return false;
}
