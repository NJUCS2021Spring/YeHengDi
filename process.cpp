//
// Created by A on 2021/2/21.
//
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "dataStruct.cpp"

std::map<std::string, word *> wrds;
std::vector<group *> grps;


std::vector<std::string> split(std::string str, const std::string &separator) {
    std::vector<std::string> result;
    int cutAt;
    while ((cutAt = str.find_first_of(separator)) != std::string::npos) {
        if (cutAt > 0) {
            result.push_back(str.substr(0, cutAt));
        }
        str = str.substr(cutAt + 1);
    }
    if (str.length() > 0) {
        result.push_back(str);
    }
    return result;
}

void readWord() {
    std::ifstream rd;
    rd.open("words.bk");
    if (rd.fail()) {
        std::cout << "Failed to read words.bk. I'm dying now.\n";
        system("pause");
        system("exit");
    }
    std::string all;
    while (std::getline(rd, all)) {
        std::vector<std::string> temp = split(all, "/");
        std::vector<std::string> ws = split(temp[1], ";");
        word *a = new word(temp[0], ws, temp[2]);
        wrds[a->name] = a;
    }
}

void readGroup() {
    std::ifstream rg;
    rg.open("groups.bk");
    if (rg.fail()) {
        std::cout << "Failed to read groups.bk. I'm dying now.\n";
        system("pause");
        system("exit");
    }
    std::string all;
    while (std::getline(rg, all)) {
        std::vector<std::string> temp = split(all, "/");
        std::vector<std::string> ws = split(temp[0], ";");
        bool isName = temp[1] == "#";
        std::vector<word *> wds;
        wds.reserve(ws.size());
        for (const std::string &i : ws) {
            wds.push_back(wrds[i]);
        }
        if (isName) {
            auto *a = new group(wds, isName);
            grps.push_back(a);
        } else {
            auto *a = new group(wds, isName, temp[1]);
            grps.push_back(a);
        }
    }
}

void load(){
    readWord();
    readGroup();
}

void mainMenu(){
    std::cout<<"\t\t---------------------------------\t\t\n"
               "\t\t|    1. check groups of word    |\t\t\n"
               "\t\t|    2. new group               |\t\t\n"
               "\t\t|    3. all groups              |\t\t\n"
               "\t\t|    4. edit word card          |\t\t\n"
               "\t\t|    5. exit()                  |\t\t\n"
               "\t\t---------------------------------\t\t\n"
               "Please select: ";
}