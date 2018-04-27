//other_fun.cpp

#include"../../include/tetrishead.hpp"
#include<fstream>
#include<vector>
#include<tuple>
#include<cstdbool>
#include<iostream>
#include<curses.h>

Direction &operator++(Direction &dir, int)
{
    auto a{static_cast<int>(dir)};
    return dir = (++a > 3) ? RIGHT : static_cast<Direction>(a);
}

void save_rezult(const std::pair<unsigned, unsigned short> &pasiblRecord)
{
    refresh();
    std::ifstream fin;
    std::ofstream fout;

    std::vector<Gamer> list{SIZE_LIST_RECORDS};
    fin.open(record_table);
    if (fin.is_open()) {
        unsigned short count_records{};
        fin >> count_records;
        refresh();
        if (count_records) {
            for (int i{}; i < count_records; ++i) {
                fin >> list[i].name_ >> list[i].rezult_.first >> list[i].rezult_.second;
                while (fin.get() != '\n')
                    continue;
            }
        }
        fin.close();
    }

    for (int i{}; i < list.size(); ++i) {
        if (list[i].rezult_ < pasiblRecord) {
            char new_name[MAX_LEN_NAME * 10];
            move(5, 0);
            for (auto i : list) {
                printw("%*s %6u %2hu\n", MAX_LEN_NAME, i.name_.c_str(), i.rezult_.first, i.rezult_.second);
            }
            mvprintw(0, 0, "Great!!! You set a new record!\nPlease enter you name:\n");
            printw("%*s %6u %2hu", MAX_LEN_NAME, " ", pasiblRecord.first, pasiblRecord.second);
            move(2, 0);
            refresh();
            echo();
            scanw("%s", new_name);
            noecho();
            list.insert(list.begin() + i, Gamer{new_name, pasiblRecord});
            list.erase(list.end());
            break;
        }
    }

    fout.open(record_table);
    if (fout.is_open()) {
        fout << list.size() << std::endl;
        for (auto i : list) {
            fout << i.name_ << " " << i.rezult_.first << " " << i.rezult_.second << std::endl;
        }
        fout.close();
    }

    clear();
    refresh();
    return;
}

void show_record_table()
{
    std::ifstream fin;
    fin.open(record_table);
    std::vector<Gamer> list{SIZE_LIST_RECORDS};
    if (fin.is_open()) {
        int count_records{};
        fin >> count_records;
        for (int i{}; i < count_records; ++i) {
            fin >> list[i].name_ >> list[i].rezult_.first >> list[i].rezult_.second;
            while (fin.get() != '\n')
                continue;
        }
        fin.close();
    }
    mvprintw (3, 0, "Record table\n");
    for (auto i : list) {
        printw("%*s %6u %2hu\n", MAX_LEN_NAME, i.name_.c_str(), i.rezult_.first, i.rezult_.second);
    }
    refresh();
    return;
}

bool operator<(std::pair<unsigned, unsigned short> &left, std::pair<unsigned, unsigned short> &right)
{
    if (left.first < right.first)
        return true;
    else
        return false;
}

Gamer::Gamer(std::string name, std::pair<unsigned, unsigned short> rezult) : name_(name), rezult_(rezult)
{
}
