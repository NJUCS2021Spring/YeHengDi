//
// Created by A on 2021/2/21.
//

#ifndef PROJECT1_PROCESS_H
#define PROJECT1_PROCESS_H
#include <vector>
#include <map>
#include "dataStruct.cpp"
extern std::map<std::string, word> wrds;
extern std::vector<group*> grps;
extern step head;
void newline();
void groupProfile(const std::vector<group*>& que);
void exit();
void readWord();
void readGroup();
void load();
void mainMenu();
void checkGroupWord();
void newGroup();
void allGroup();
void editWord();
#endif //PROJECT1_PROCESS_H
