//
// define some classes to be used.
//

#include "dataStruct.h"
#include <utility>
#include <vector>
#include <iostream>

class word {
private:
    std::string name;
    std::vector<std::string> meaning;
    std::string example;
public:
    word(std::string name, std::vector<std::string> meanings, std::string example) {
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
                  << "\t释义：";
        if (wrd.meaning.empty()) {
            std::cout << "无";
        } else {
            for (const std::string& i: wrd.meaning) {
                std::cout << i << ';';
            }
        }
        std::cout << std::endl << "\t例句：" << wrd.example;
    }

    void addMeaning(const std::string& m){
        this->meaning.push_back(m);
    }

    void addExample(const std::string& e){
        this->example = e;
    }

    static void write(const word& wrd){
        
    }
};

class group{
private:
    int globalID = 0;
    int id;
    std::vector<std::string> words;
    bool isName;
    std::string reason;
public:
    group(const std::vector<std::string>& wrds, bool isName, const std::string& reason){
        this->id = globalID;
        globalID++;
        this->words = wrds;
        this->isName = isName;
        this->reason = reason;
    }
};