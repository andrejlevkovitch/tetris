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
enum Cell{DEFAULT_CELL, FRAME_CELL, FREE_CELL, BRICK_R_CELL, BRICK_G_CELL, BRICK_Y_CELL, BRICK_B_CELL, BRICK_C_CELL, BRICK_M_CELL};

const chtype DEF_VALUE{' ' | COLOR_PAIR(FREE_CELL)};
const std::vector<chtype>BLOCKS{' ' | COLOR_PAIR(BRICK_R_CELL),
                                ' ' | COLOR_PAIR(BRICK_G_CELL),
                                ' ' | COLOR_PAIR(BRICK_Y_CELL),
                                ' ' | COLOR_PAIR(BRICK_B_CELL),
                                ' ' | COLOR_PAIR(BRICK_C_CELL),
                                ' ' | COLOR_PAIR(BRICK_M_CELL),
};

const unsigned NBrTy{7};
enum BrickType{BRICK_I, BRICK_J, BRICK_L, BRICK_O, BRICK_S, BRICK_T, BRICK_Z};

enum Direction{RIGHT, DOWN, LEFT, UP};

class Brick;
class Koords {
    private:
        short y_;
        short x_;
        static const unsigned PASSIDE{2};
        static const unsigned PASFRWD{1};
    public:
        template<typename T, typename P>
            Koords(T y = 0, P x = 0) : y_(y), x_(x){};
        Koords(const Koords &);
        auto getY() const -> decltype(y_);
        auto getX() const -> decltype(x_);
        bool operator<(const Koords &) const;
        bool operator>(const Koords &) const;
        Koords &operator=(const Brick &);
        Koords operator-(const Koords &) const;
        Koords operator+(const Koords &) const;
        bool operator==(const Koords &) const;
        Koords &move_right();
        Koords &move_left();
        Koords &move_up();
        Koords &move_down();
        Koords &to_index();
};

const Koords BEGSCR{5, 9};
const Koords ENDSCR{BEGSCR + Koords{SIZEY + 1, SIZEX * 2 + 1}};
const Koords INPOSITION{BEGSCR + Koords{2, SIZEX + 1}};
const Koords DEFCENTER{0, 1};
const Koords SHOWPOSITION{Koords{BEGSCR + Koords{5, 30}}};

typedef std::vector<std::vector<chtype>> Field;

class Brick {
    private:
        BrickType name_;
        Direction beg_direction_;
        Direction direction_;
        Field field_;
        Koords position_;
        Koords center_;
        chtype block_;
    public:
        Brick();
        ~Brick();
        const Brick &show(chtype = BLOCKS[0]) const;
        Brick &rotade(Field &);
        bool down(Field &);
        Brick &left(Field &);
        Brick &right(Field &);
        const Koords &get_koords() const;
        std::pair<Koords, Koords> sides() const;
        Field get_block() const;
    private:
        const Brick &clean() const;
        Brick &rotor();
        bool is_pasible(Field &) const;
};

class Tetris {
    private:
        Field screen_;
        Brick current_;
    public:
        Tetris();
        ~Tetris();
        void game();
    private:
        void frame() const;
        void print_screen() const;
        void intake(const Brick &);
        bool delete_all_solutions();
};

void move_at(const Koords &);
void move_add(const Koords &, chtype);
int init_colors(void);
Direction &operator++(Direction &, int);
