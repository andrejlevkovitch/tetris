//cords.cpp

#include"../../include/tetrishead.hpp"

Koords::Koords(const int y, const int x) : y_(y), x_(x)
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
