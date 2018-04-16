//tetrishead.hpp

#include<vector>
#include<string>
#include<curses.h>

const unsigned SIZEY{20};
const unsigned SIZEX{10};

const unsigned BYSCREEN{5};
const unsigned BXSCREEN{9};

const unsigned INPUTBRICKY{BYSCREEN + 1};
const unsigned INPUTBRICKX{BXSCREEN + SIZEX - 2};

const int ESC{033};
const int ENTER{012};

//all cells
enum Cell{DEFAULT_CELL, FRAME_CELL, FREE_CELL, BRICK_CELL};

const chtype DEF_VALUE{' ' | COLOR_PAIR(FREE_CELL)};
const chtype BLOCK{' ' | COLOR_PAIR(BRICK_CELL)};

enum BrickType{BRICK_I, BRICK_J, BRICK_L, BRICK_O, BRICK_S, BRICK_T, BRICK_Z};

enum Direction{RIGHT, DOUWN, LEFT, UP};

class Koords {
    private:
        unsigned short y_;
        unsigned short x_;
    public:
        Koords(const int y = 0, const int x = 0);
        auto getY() const -> decltype(y_);
        auto getX() const -> decltype(x_);
};

class Brick {
    private:
        std::vector<std::vector<chtype>> field_;
        Direction direction_;
        Koords position_;
    public:
        explicit Brick(const BrickType = BRICK_I);
        ~Brick();
        void show() const;
        void rotade();
};

class Tetris {
    private:
        std::vector<std::vector<chtype>> field_;
        decltype(field_) screen_;
        Koords beginen_;
        Koords end_;
    public:
        Tetris();
        ~Tetris();
        void game();
    private:
        void frame() const;
        void print_screen() const;
};

void move_at(const Koords &);
int init_colors(void);
