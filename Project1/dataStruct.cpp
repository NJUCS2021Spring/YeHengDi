//
// define some classes to be used.
//

#include "dataStruct.h"
#include <cstring>
#include <algorithm>
#include <fstream>
#include <utility>
#include <vector>
#include <iostream>

class word {
private:

    std::vector<std::string> meaning;
    std::string example;
public:
    std::string name;

    word(std::string name, std::vector<std::string> meanings = {}, std::string example = "") {
        this->name = std::move(name);
        this->meaning = std::move(meanings);
        this->example = std::move(example);
    }

    word() {
        std::string temp;
        std::cout << "Please enter word name: ";
        std::cin >> this->name;
        std::cout << '\n'
                  << "Please enter meanings, using '#' as the end: ";
        while (std::cin >> temp) {
            if (temp == "#") {
                break;
            }
            this->meaning.push_back(temp);
        }
        std::cout << '\n'
                  << "Please add an example sentence: " << std::endl;
        getchar();
        getline(std::cin, this->example);
    }

    static void display(const word& wrd) {
        std::cout << wrd.name << std::endl
                  << "\tMeanings: ";
        if (wrd.meaning.empty()) {
            std::cout << "None";
        } else {
            for (const std::string& i: wrd.meaning) {
                std::cout << i << ';';
            }
        }
        std::cout << std::endl << "\tExample: " << wrd.example<<'\n';
    }

    void addMeaning(const std::string& m){
        this->meaning.push_back(m);
    }

    void addExample(const std::string& e){
        this->example = e;
    }

    static void write(const word& wrd){
        std::ofstream pt;
        pt.open("words.bk", std::ios::app);
        if(pt.fail()){
            std::cout<<"Fail to open file.";
            return;
        }
        pt<<wrd.name<<'/';
        for(const std::string &i : wrd.meaning){
            pt<<i<<';';
        }
        pt<<'/'<<wrd.example<<'\n';
        pt.close();
    }
};

class group{
private:
    unsigned globalID = 0;
    unsigned id;
    std::vector<word> words;
    bool isName;
    std::string reason;
    static bool sortword(const word& A, const word& B){
        int i;
        std::string a = A.name,b = B.name;
        for(i = 0;a[i] != '\0' && b[i] != '\0';i++){
            a[i] = tolower(a[i]),b[i] = tolower(b[i]);
            int j = int(a[i] - b[i]);
            if (!j){
                return j < 0;
            }
        }
        return a[i] == '\0';
    }
    void srt(){
        sort(this->words.begin(), this->words.end(),sortword);
    }
public:
    group(const std::vector<word>& wrds = {}, bool isName = true, const std::string& reason = ""){
        this->id = globalID;
        globalID++;
        this->words = wrds;
        this->isName = isName;
        this->reason = reason;
    }

    void addMember(const word& wrd){
        this->words.push_back(wrd);
        this->srt();
    }

    static void display(group grp){
        std::cout<<"Words: ";
        for(const word& i:grp.words){
            std::cout<<i.name<<" ";
        }
        std::cout<<'\n';
        if(!grp.isName){
            std::cout<<"Category: "<<grp.reason<<'\n';
        }
        std::cout<<"Word cards: \n";
        for(unsigned i = 0;i<grp.words.size();i++){
            std::cout<<i + 1<<". ";
            word::display(grp.words[i]);
        }
    }

    static void write(const group& grp){
        std::ofstream w;
        w.open("words.bk", std::ios::app);
        std::string meaning;
        w<<grp.id<<'/';
        for (const word& i : grp.words)
        {
            w<<i.name<<';';
        }
        w<<'/'<<(grp.isName?"#":grp.reason)<<'\n';
        w.close();
    }
};