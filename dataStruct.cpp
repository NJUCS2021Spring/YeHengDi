//
// define some classes to be used.
//

#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iostream>

class word {
private:

    std::vector<std::string> meaning;
    std::string example;
public:
    std::string name;

    explicit word(std::string name, std::vector<std::string> meanings = {}, std::string example = "None") {
        this->name = std::move(name);
        this->meaning = std::move(meanings);
        this->example = std::move(example);
    }


    static void display(word *wrd) {
        std::cout << wrd->name << std::endl
                  << "\tMeanings: ";
        if (wrd->meaning.empty()) {
            std::cout << "None";
        } else {
            for (const std::string &i: wrd->meaning) {
                std::cout << i << ';';
            }
        }
        std::cout << std::endl << "\tExample: " << wrd->example << '\n';
    }

    void addMeaning(const std::string &m) {
        this->meaning.push_back(m);
    }

    void addExample(const std::string &e) {
        this->example = e;
    }

    static void write(const word &wrd) {
        std::ofstream pt;
        pt.open("data/words.bk", std::ios::app);
        if (pt.fail()) {
            std::cout << "Fail to open file.";
            return;
        }
        pt << wrd.name << '/';
        for (const std::string &i : wrd.meaning) {
            pt << i << ';';
        }
        pt << '/' << wrd.example << '\n';
        pt.close();
    }

    std::string toStr(){
        std::string str = this->name + '/';
        for (const std::string &i : this->meaning){
            str += i + ';';
        }
        str += '/' + this->example;
        return str;
    }

};//word class.
static unsigned globalID = 0;
class group {
private:

    unsigned id;
    bool isName;

    static bool sortword(word *A, word *B) {
        return mystrCmp(A->name, B->name);
    }

    void srt() {
        sort(this->words.begin(), this->words.end(), sortword);
    }

public:
    std::string reason;
    std::vector<word *> words;
    explicit group(const std::vector<word *> &wrds = {}, bool isName = true, const std::string &reason = "") {
        this->id = globalID;
        globalID++;
        this->words = wrds;
        this->isName = isName;
        this->reason = reason;
        this->srt();
    }

    static bool mystrCmp(std::string a, std::string b) {
        int i;
        for (i = 0; a[i] != '\0' && b[i] != '\0'; i++) {
            a[i] = tolower(a[i]), b[i] = tolower(b[i]);
            int j = int(a[i] - b[i]);
            if (j) {
                return j < 0;
            }
        }
        return a[i] == '\0';
    }

    void addMember(word *wrd) {
        if(find(this->words.begin(),this->words.end(), wrd) == this->words.end()) {
            this->words.push_back(wrd);
            this->srt();
        }
    }

    unsigned ID(){
        return this->id;
    }

    bool Reason(){
        return this->isName;
    }

    static void display(group grp) {
        std::cout << "Words: ";
        for (const word *i:grp.words) {
            std::cout << i->name << " ";
        }
        std::cout << '\n';
        if (!grp.isName) {
            std::cout << "Category: " << grp.reason << '\n';
        }
        std::cout << "Word cards: \n";
        for (unsigned i = 0; i < grp.words.size(); i++) {
            std::cout << i + 1 << ". ";
            word::display(grp.words[i]);
        }
    }

    static void write(const group &grp) {
        std::ofstream w;
        w.open("data/groups.bk", std::ios::app);
        std::string meaning;
        for (const word *i : grp.words) {
            w << i->name << ';';
        }
        w << '/' << (grp.isName ? "#" : grp.reason) << '\n';
        w.close();
    }

    std::string toStr(){
        std::string str;
        for(const word *i : this->words){
            str += i->name + ';';
        }
        str += '/' + (this->isName ? "#" : this->reason);
        return str;
    }

};//group class.