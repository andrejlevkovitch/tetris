//other_fun.cpp

#include"../../include/tetrishead.hpp"
#include<fstream>
#include<vector>
#include<tuple>
#include<cstdbool>
#include<curses.h>

#define STRLEN_(x) #x
#define STRLEN(x) STRLEN_(x)

Direction &operator++(Direction &dir, int)
{
    auto a{static_cast<int>(dir)};
    return dir = (++a > 3) ? RIGHT : static_cast<Direction>(a);
}

Gamer::Gamer(std::string name, Rpair rezult) : name_(name), rezult_(rezult)
{
}

void save_rezult(const Rpair &pasiblRecord)
{
    refresh();

    std::vector<Gamer> list{SIZE_LIST_RECORDS};
    read_from_file(list);

    for (int i{}; i < list.size(); ++i) {
        if (list[i].rezult_ < pasiblRecord) {
            char new_name[MAX_LEN_NAME];
            std::string nName;
            show_record_table();
            mvprintw(0, 0, "Great!!! You set a new record!\nPlease enter you name:\n");
            printw("%*s %6u %2hu", MAX_LEN_NAME, " ", pasiblRecord.first, pasiblRecord.second);
            move(2, 0);
            refresh();
            echo();
            scanw("%" STRLEN(MAX_LEN_NAME) "s", new_name);
            nName = new_name;
            if (!nName.size()) {
                nName = "default";
            }
            noecho();
            list.insert(list.begin() + i, Gamer{nName, pasiblRecord});
            list.erase(list.end());
            break;
        }
    }

    save_in_file(list);

    clear();
    refresh();
    return;
}

void read_from_file(std::vector<Gamer> &from)
{
    std::ifstream fin;
    fin.open(record_table);
    if (fin.is_open()) {
        unsigned short count_records{};
        fin >> count_records;
        refresh();
        if (count_records) {
            for (int i{}; i < count_records; ++i) {
                fin >> from[i].name_ >> from[i].rezult_.first >> from[i].rezult_.second;
                while (fin.get() != '\n')
                    continue;
            }
        }
        else {
            save_in_file(from);
        }
        fin.close();
    }
    return;
}

void save_in_file(std::vector<Gamer> &in)
{
    std::ofstream fout;
    fout.open(record_table);
    if (fout.is_open()) {
        fout << in.size() << std::endl;
        for (auto &i : in) {
            fout << i.name_ << " " << i.rezult_.first << " " << i.rezult_.second << std::endl;
        }
        fout.close();
    }
    return;
}

void show_record_table()
{
    std::vector<Gamer> list{SIZE_LIST_RECORDS};
    read_from_file(list);
    mvprintw (5, 0, "Record table\n");
    for (const auto &i : list) {
        printw("%*s %6u %2hu\n", MAX_LEN_NAME, i.name_.c_str(), i.rezult_.first, i.rezult_.second);
    }
    refresh();
    return;
}

bool operator<(Rpair &left, Rpair &right)
{
    if (left.first < right.first)
        return true;
    else
        return false;
}
