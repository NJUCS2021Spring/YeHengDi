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
void newWord();
void newline();
void groupProfile(const std::vector<group*>& que);
void exit();
void readWord();
void readGroup();
void editW();
void load();
void mainMenu();
void allWord();
void checkGroupWord();
void newGroup();
void allGroup();
void editWordCard();
#endif //PROJECT1_PROCESS_H
