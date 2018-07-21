// gamer.cpp

#include "tetrishead.hpp"
#include <cctype>
#include <cstdbool>
#include <curses.h>
#include <fstream>
#include <tuple>

#define STRLEN_(x) #x
#define STRLEN(x) STRLEN_(x)

Gamer::Gamer(std::string name, Rpair rezult) : name_(name), rezult_(rezult) {}

Gamer::~Gamer() {}

bool Gamer::operator<(const Rpair &right) const { return rezult_ < right; }

void save_rezult(const Rpair &pasiblRecord) {
  refresh();

  std::list<Gamer> gamerList{SIZE_LIST_RECORDS};
  read_from_file(gamerList);

  for (auto i{gamerList.begin()}; i != gamerList.end(); ++i) {
    if (*i < pasiblRecord) {
      char new_name[MAX_LEN_NAME + 1] = "";
      std::string nName;
      show_record_table();
      mvprintw(0, 0,
               "Great!!! You set a new record!\nPlease enter you name:\n");
      printw("%*s %6u %2hu", MAX_LEN_NAME, " ", pasiblRecord.first,
             pasiblRecord.second);
      move(2, 0);
      refresh();
      echo();
      scanw("%" STRLEN(MAX_LEN_NAME) "s", new_name);
      for (int i{}; std::isalpha(new_name[i]); ++i) {
        nName += new_name[i];
      }
      if (!nName.size()) {
        nName = "default";
      }
      noecho();
      gamerList.insert(i, Gamer{nName, pasiblRecord});
      gamerList.pop_back();
      break;
    }
  }

  save_in_file(gamerList);

  clear();
  refresh();
  return;
}

std::ifstream &operator>>(std::ifstream &fin, Gamer &in) {
  fin >> in.name_ >> in.rezult_.first >> in.rezult_.second;
  return fin;
}

std::ofstream &operator<<(std::ofstream &fout, Gamer &out) {
  fout << out.name_ << " " << out.rezult_.first << " " << out.rezult_.second
       << std::endl;
  return fout;
}
