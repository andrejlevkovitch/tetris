//cords.cpp

#include"../../include/tetrishead.hpp"
#include<cstdbool>

Koords::Koords(const unsigned y, const unsigned x) : y_(y), x_(x)
{
}

Koords::Koords(const Koords &in, const int y, const int x) : y_(in.y_ + y), x_(in.x_ + x)
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
    x_ += PASSIDE;
    return *this;
}

Koords &Koords::move_left()
{
    x_ -= PASSIDE;
    return *this;
}

Koords &Koords::move_up()
{
    y_ -= PASFRWD;
    return *this;
}

Koords &Koords::move_down()
{
    y_ += PASFRWD;
    return *this;
}

Koords &Koords::to_index()
{
    *this = *this - BEGSCR - Koords{1, 1};
    *this = Koords{y_, x_ / 2};
    return *this;
}

Koords Koords::operator-(const Koords &right) const
{
    return Koords{y_ - right.y_, x_ - right.x_};
}

Koords &Koords::operator=(const Brick &in)
{
    return *this = in.get_koords();
}
