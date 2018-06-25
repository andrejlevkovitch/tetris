//other_fun.cpp

#include"tetrishead.hpp"
#include<fstream>
#include<tuple>
#include<curses.h>
#include<list>
#include<algorithm>

Direction &operator++(Direction &dir, int)
{
    auto a {static_cast<int>(dir)};
    return dir = (++a > 3) ? RIGHT : static_cast<Direction> (a);
}

void show_record_table()
{
    std::list<Gamer> gamerList {SIZE_LIST_RECORDS};
    read_from_file(gamerList);
    mvprintw (5, 0, "Record table\n");
    for (const auto &i : gamerList) {
        printw("%*s %6u %2hu\n", MAX_LEN_NAME, i.name_.c_str(), i.rezult_.first, i.rezult_.second);
    }
    refresh();
    return;
}

void read_from_file(std::list<Gamer> &from)
{
    std::ifstream fin;
    fin.open(RECORD_TABLE);
    if (fin.is_open()) {
        unsigned short count_records{};
        fin >> count_records;
        refresh();
        if (count_records) {
            std::for_each(from.begin(), from.end(), [&](auto &i){fin >> i;});
        }
        else {
            save_in_file(from);
        }
        fin.close();
    }
    return;
}

void save_in_file(std::list<Gamer> &in)
{
    std::ofstream fout;
    fout.open(RECORD_TABLE);
    if (fout.is_open()) {
        fout << in.size() << std::endl;
        std::for_each(in.begin(), in.end(), [&](auto &i){fout << i;});
        fout.close();
    }
    return;
}
