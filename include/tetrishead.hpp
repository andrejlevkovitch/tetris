//tetrishead.hpp

#ifndef TETHEAD
#define TETHEAD

#ifndef __cplusplus
#error C++ is required
#elif __cplusplus <= 201103L
#error C++14 is required
#endif

#include<vector>
#include<list>
#include<curses.h>
#include<cstdbool>
#include<cstdlib>
#include<tuple>
#include<fstream>
#include<chrono>
#include<deque>

#define MAX_LEN_NAME 10

typedef std::vector<std::vector<chtype>> Field;
typedef std::deque<std::vector<chtype>> TetrisScreen;
typedef std::pair<unsigned, unsigned short> Rpair;

#ifdef __linux__
const std::string HOME {getenv("HOME")};
#else
const std::string HOME {getenv("LOCALAPPDATA")};
#endif
const std::string RECORD_TABLE {HOME + "/.tetris_record_table.txt"};

const unsigned SIZE_Y {20};
const unsigned SIZE_X {10};

const std::chrono::milliseconds BEGIN_TIME_DOWN {800};
const unsigned LINES_TO_NEW_LEVEL {8};

const unsigned SIZE_LIST_RECORDS {10};

const int ESC {033};
const int ENTER {012};
const int PAUSE {' '};

enum Cell {DEFAULT_CELL, FRAME_CELL, FREE_CELL, BRICK_R_CELL, BRICK_G_CELL, BRICK_Y_CELL, BRICK_B_CELL, BRICK_C_CELL, BRICK_M_CELL};

enum Direction {RIGHT, DOWN, LEFT, UP};
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
    private:
        std::string name_;
        Rpair rezult_;
    public:
        Gamer (std::string = "default", Rpair = Rpair{0, 0});
        ~Gamer();
        bool operator<(const Rpair &) const;
        friend void show_record_table();
        friend std::ifstream &operator>>(std::ifstream &, Gamer &);
        friend std::ofstream &operator<<(std::ofstream &, Gamer &);
};

class Koords {
    private:
        short y_;
        short x_;
        static const unsigned PAS_SIDE{2};
        static const unsigned PAS_FRWD{1};
    public:
        explicit Koords (short = 0, short = 0);
        Koords(const Koords &);
        auto getY() const -> decltype(y_);
        auto getX() const -> decltype(x_);
        bool operator<(const Koords &) const;
        bool operator>(const Koords &) const;
        Koords operator-(const Koords &) const;
        Koords operator+(const Koords &) const;
        bool operator==(const Koords &) const;
        Koords &move_right();
        Koords &move_left();
        Koords &move_up();
        Koords &move_down();
        Koords &to_index();
};

const Koords BEG_SCR {0, 0};
const Koords END_SCR {BEG_SCR + Koords{SIZE_Y + 1, SIZE_X * 2 + 1}};
const Koords IN_POSITION {BEG_SCR + Koords{0, SIZE_X + 1}};
const Koords DEF_CENTRUM {0, 1};
const Koords SHOW_POSITION {Koords{END_SCR + Koords(- END_SCR.getY() + BEG_SCR.getY() + 3, 10)}};
const Koords SCORE {SHOW_POSITION + Koords{3, - 4}};
const Koords END_GAME_MESAGE {Koords{BEG_SCR + Koords(SIZE_Y / 2, SIZE_X - 5)}};
const Koords BUFFER_PLACE {3, 0};

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
        Brick ();
        ~Brick();
        const Brick &show(chtype = BLOCKS[0]) const;
        Brick &rotade(TetrisScreen &);
        bool down(TetrisScreen &);
        void left(TetrisScreen &);
        void right(TetrisScreen &);
        const Koords &get_koords() const;
        std::pair<Koords, Koords> sides() const;
        Field get_block() const;
    private:
        Brick &rotor();
        bool is_pasible(TetrisScreen &) const;
};

class Tetris {
    private:
        enum Score{ONE = 100, TWO = 300, TRI = 700, TET = 1500};
    private:
        TetrisScreen screen_;
        Brick currentBrick_;
        unsigned score_;
        unsigned short level_;
        unsigned short lines_;
    public:
        Tetris ();
        ~Tetris();
        Rpair game();
    private:
        void frame() const;
        void print_screen() const;
        void print_level() const;
        void intake();//throws an exception!!!
        unsigned short delete_all_solutions();
};

void move_at(const Koords &);
void move_add(const Koords &, chtype);
void init_colors(void);//throws an exception!!!
int input();
void save_rezult(const Rpair &);
void read_from_file(std::list<Gamer> &);
void save_in_file(std::list<Gamer> &);
void show_record_table();

#endif
