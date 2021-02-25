//
// Created by A on 2021/2/21.
//

#ifndef PROJECT1_PROCESS_H
#define PROJECT1_PROCESS_H

#include <vector>
#include <map>
#include "dataStruct.cpp"

extern std::map<std::string, word *> wrds;
extern std::vector<group *> grps;

std::map<std::string, word*> searchW(bool(*comp)(word*,const std::string&),const std::string& flag, const std::map<std::string, word *>& bank = wrds);

void errorProcess(const std::string &msg, void(*func)());

void newWord();

void newline();

void groupProfile(const std::vector<group *> &que);

void readWord();

void readGroup();

void singWords(const std::map<std::string,word*>& bank = wrds);

void editW();

bool strMatch(const std::string& target, const std::string& feature);

void load();

void mainMenu();

void allWord();

void search();

void newGroup();

void groupEdit();

void allGroup();

void editWordCard();

void modifyLineData(char *fileName, unsigned lineNum, const std::string& lineData);

int getLineNumber(std::ifstream &a, const std::string &name);

#endif //PROJECT1_PROCESS_H
