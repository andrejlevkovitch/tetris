//tetrishead.hpp

#include<vector>
#include<curses.h>
#include<cstdbool>
#include<tuple>

const unsigned SIZEY{20};
const unsigned SIZEX{10};

const int ESC{033};
const int ENTER{012};

//all cells
enum Cell{DEFAULT_CELL, FRAME_CELL, FREE_CELL, BRICK_CELL};

const chtype DEF_VALUE{' ' | COLOR_PAIR(FREE_CELL)};
const chtype BLOCK{' ' | COLOR_PAIR(BRICK_CELL)};

const unsigned NBrTy{7};
enum BrickType{BRICK_I, BRICK_J, BRICK_L, BRICK_O, BRICK_S, BRICK_T, BRICK_Z};

enum Direction{RIGHT, DOWN, LEFT, UP};

class Brick;
class Koords {
    private:
        unsigned y_;
        unsigned x_;
        static const unsigned PASSIDE{2};
        static const unsigned PASFRWD{1};
    public:
        explicit Koords(const unsigned y = 0, const unsigned x = 0);
        Koords(const Koords &, const int y = 0, const int x = 0);
        auto getY() const -> decltype(y_);
        auto getX() const -> decltype(x_);
        bool operator<(const Koords &) const;
        bool operator>(const Koords &) const;
        Koords &operator=(const Brick &);
        Koords operator-(const Koords &) const;
        Koords &move_right();
        Koords &move_left();
        Koords &move_up();
        Koords &move_down();
        Koords &to_index();
};

const Koords BEGSCR{5, 9};
const Koords ENDSCR{BEGSCR, SIZEY + 1, SIZEX * 2 + 1};
const Koords INPOSITION{BEGSCR, 0, SIZEX + 1};

class Brick {
    private:
        std::vector<std::vector<chtype>> field_;
        Direction direction_;
        Koords position_;
    public:
        explicit Brick(const BrickType & = BRICK_I);
        ~Brick();
        const Brick &show(const chtype = BLOCK) const;
        Brick &rotade();
        bool down();
        Brick &left();
        Brick &right();
        Brick &next();
        const Koords &get_koords() const;
    private:
        const Brick &clean() const;
        std::pair<Koords, Koords> sides() const;
};

class Tetris {
    private:
        std::vector<std::vector<chtype>> screen_;
    public:
        Tetris();
        ~Tetris();
        void game();
    private:
        void frame() const;
        void print_screen() const;
        void intake(const Brick &);
};

void move_at(const Koords &);
void move_add(const Koords &, chtype);
int init_colors(void);
