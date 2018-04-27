//tetrishead.hpp

#include<vector>
#include<curses.h>
#include<cstdbool>
#include<tuple>
#include<mutex>
#include<stdio.h>

const std::string HOME{getenv("HOME")};
const std::string record_table{HOME + "/.tetris_record_table.txt"};

const unsigned SIZE_Y{20};
const unsigned SIZE_X{10};

const unsigned BEGIN_TIME_DOWN{1000};
const unsigned LINES_TO_NEW_LEVEL{8};

const unsigned SIZE_LIST_RECORDS{10};
const unsigned MAX_LEN_NAME{10};

const int ESC{033};
const int ENTER{012};

enum Cell{DEFAULT_CELL, FRAME_CELL, FREE_CELL, BRICK_R_CELL, BRICK_G_CELL, BRICK_Y_CELL, BRICK_B_CELL, BRICK_C_CELL, BRICK_M_CELL};

enum Direction{RIGHT, DOWN, LEFT, UP};
Direction &operator++(Direction &, int);

const chtype DEF_VALUE{' ' | COLOR_PAIR(FREE_CELL)};
const std::vector<chtype>BLOCKS{' ' | COLOR_PAIR(BRICK_R_CELL),
                                ' ' | COLOR_PAIR(BRICK_G_CELL),
                                ' ' | COLOR_PAIR(BRICK_Y_CELL),
                                ' ' | COLOR_PAIR(BRICK_B_CELL),
                                ' ' | COLOR_PAIR(BRICK_C_CELL),
                                ' ' | COLOR_PAIR(BRICK_M_CELL),
};

class Gamer {
    public:
        std::string name_;
        std::pair<unsigned, unsigned short> rezult_;
        Gamer(std::string = "default", std::pair<unsigned, unsigned short> = std::pair<unsigned, unsigned short>{0, 0});
};

static std::mutex threadMutex;

class Brick;
class Koords {
    private:
        short y_;
        short x_;
        static const unsigned PAS_SIDE{2};
        static const unsigned PAS_FRWD{1};
    public:
        template<typename T, typename P>
            explicit Koords(T y = 0, P x = 0) : y_(y), x_(x) {};
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

const Koords BEG_SCR{5, 9};
const Koords END_SCR{BEG_SCR + Koords{SIZE_Y + 1, SIZE_X * 2 + 1}};
const Koords IN_POSITION{Koords{BEG_SCR + Koords{0, SIZE_X + 1}}};
const Koords DEF_CENTRUM{0, 1};
const Koords SHOW_POSITION{Koords{BEG_SCR + Koords{3, 30}}};
const Koords SCORE{BEG_SCR + Koords{6, 26}};
const Koords END_GAME_MESAGE{Koords{BEG_SCR + Koords{10, 6}}};
const Koords BUFFER_PLACE{3, 0};

typedef std::vector<std::vector<chtype>> Field;

class Brick {
    private:
        static const unsigned N_BRICK_KIND{7};
        enum BrickType{BRICK_I, BRICK_J, BRICK_L, BRICK_O, BRICK_S, BRICK_T, BRICK_Z};
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
        Brick &rotor();
        bool is_pasible(Field &) const;
};

class Tetris {
    private:
        enum Score{ONE = 100, TWO = 300, TRI = 700, TET = 1500};
    private:
        Field screen_;
        Brick currentBrick_;
        unsigned score_;
        unsigned short level_;
        unsigned short lines_;
    public:
        Tetris();
        ~Tetris();
        std::pair<decltype(score_), decltype(level_)> game();
    private:
        void frame() const;
        void print_screen() const;
        bool intake();
        unsigned short delete_all_solutions();
};

void move_at(const Koords &);
void move_add(const Koords &, chtype);
int init_colors(void);
int is_input();
void endless(const bool &, int &, unsigned short &);
void save_rezult(const std::pair<unsigned, unsigned short> &);
bool operator<(std::pair<unsigned, unsigned short> &, std::pair<unsigned, unsigned short> &);
void show_record_table();
