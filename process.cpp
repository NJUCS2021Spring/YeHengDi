//
// Created by A on 2021/2/21.
//
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include "dataStruct.cpp"

using namespace std;

map<string, word *> wrds;
vector<group *> grps;

map<string, word*> searchW(bool(*comp)(word*,const string&),const string& flag, const map<string, word *>& bank = wrds){
    map<string,word*> res;
    for(auto& i:bank){
        if (comp(i.second,flag)){
            res[i.first] = i.second;
        }
    }
    return res;
}

void errorProcess(const string &msg, void(*func)()) {
    while (cin.fail()) {
        cout << msg << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        func();
    }
}

void modifyLineData(char *fileName, int lineNum, string lineData) {
    ifstream in;
    in.open(fileName);
    string strFileData;
    int line = 1;
    char tmpLineData[1024] = {0};
    while (in.getline(tmpLineData, sizeof(tmpLineData))) {
        if (line == lineNum) {
            strFileData += lineData;
            strFileData += "\n";
        } else {
            strFileData += tmpLineData;
            strFileData += "\n";
        }
        line++;
    }
    in.close();

    //写入文件
    ofstream out;
    out.open(fileName);
    out.flush();
    out << strFileData;
    out.close();
}

vector<string> split(string str, const string &separator) {
    vector<string> result;
    int cutAt;
    while ((cutAt = str.find_first_of(separator)) != string::npos) {
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

int getLineNumber(ifstream &a, const string &name) {
    string tmp;
    int i = 0;
    for (; tmp != name; i++, getline(a, tmp), tmp = split(tmp, "/")[0]);
    return i;
}

void newline() {
    cout << "-----------------------------------------------------------------------\n";
}

void groupProfile(const vector<group *> &que) {
    if (que.empty()) {
        return;
    }
    newline();
    cout << "ID\t\t\t\tWords\t\t\t\tReason\t\t\t\t\n";//61_
    for (auto *i:que) {
        cout << left << setw(30) << i->ID();
        int count = 2;
        for (auto *w:i->words) {
            if (count) {
                cout << w->name << ",";
                count--;
            } else {
                cout << "...";
                break;
            }
        }
        cout << setw(2) << "";
        if (i->Reason()) {
            cout << right << setw(29) << "Name\n";
        } else {
            cout << right << setw(25) << "Meaning-" << i->reason << '\n';
        }
    }
    newline();
}

void readWord() {
    ifstream rd;
    rd.open("data/words.bk", ios::app);
    if (rd.fail()) {
        cout << "Failed to read words.bk. I'm dying now.\n";
        system("pause");
        exit(114514);
    }
    string all;
    while (getline(rd, all)) {
        if (all.empty()) {
            continue;
        }
        vector<string> temp = split(all, "/");
        vector<string> ws = split(temp[1], ";");
        word *a = new word(temp[0], ws, temp[2]);
        wrds[a->name] = a;
    }
}

void readGroup() {
    ifstream rg;
    rg.open("data/groups.bk", ios::app);
    if (rg.fail()) {
        cout << "Failed to read groups.bk. I'm dying now.\n";
        system("pause");
        exit(114514);
    }
    string all;
    while (getline(rg, all)) {
        if (all.empty()) {
            continue;
        }
        vector<string> temp = split(all, "/");
        vector<string> ws = split(temp[0], ";");
        bool isName = temp[1] == "#";
        vector<word *> wds;
        wds.reserve(ws.size());
        for (const string &i : ws) {
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

void singWords(const map<string,word*>& bank = wrds){
    newline();
    cout << "All Words:\n";
    for (const auto &i:bank) {
        cout << i.first << " ";
    }
    cout << '\n';
    newline();
}

void load() {
    readWord();
    readGroup();
}

void mainMenu() {
    cout << "\t\t---------------------------------\t\t\n"
            "\t\t|    1. search...               |\t\t\n"
            "\t\t|    2. new group               |\t\t\n"
            "\t\t|    3. all groups              |\t\t\n"
            "\t\t|    4. edit word card          |\t\t\n"
            "\t\t|    5. new word                |\t\t\n"
            "\t\t|    6. exit()                  |\t\t\n"
            "\t\t---------------------------------\t\t\n"
            "Please select: ";
}

void allWord() {
    singWords();
}

void editW(word *wd) {
    cout << "\t\t-----------------------\t\t\n"
            "\t\t|    1. new example   |\t\t\n"
            "\t\t|    2. new meaning   |\t\t\n"
            "\t\t|    3. exit()        |\t\t\n"
            "\t\t-----------------------\t\t\n";
    cout << "Please choose:";
    int i;
    cin >> i;
    while (i - 3) {
        string ex;
        if (i == 1) {
            cout << "Enter new example.\n>>> ";
            getchar();
            getline(cin, ex);
            wd->addExample(ex);
        } else if (i == 2) {
            cout << "Enter new meaning.\n>>> ";
            cin >> ex;
            wd->addMeaning(ex);
        }
        ifstream b("data/words.bk", ios::app);
        modifyLineData("data/words.bk", getLineNumber(b, wd->name), wd->toStr());
        cout << "Please choose:";
        cin >> i;
    }
}

void groupEdit(group *g) {
    cout << "\t\t--------------------------\t\t\n"
            "\t\t|      1.add word        |\t\t\n"
            "\t\t|      2.edit words      |\t\t\n"
            "\t\t|      3.exit()          |\t\t\n"
            "\t\t--------------------------\t\t\n";
    int i;
    cout << "Please choose one.\n>>> ";
    cin >> i;
    while (i - 3) {
        if (i == 1) {
            cout << "Please enter word.\n>>> ";
            string name;
            cin >> name;
            if (wrds.count(name)) {
                g->addMember(wrds[name]);
            } else {
                word *w = new word(name);
                word::write(*w);
                wrds[name] = w;
                g->addMember(w);
            }
        } else if (i == 2) {
            cout << "Please enter word.\n>>> ";
            string name;
            cin >> name;
            if (wrds.count(name)) {
                editW(wrds[name]);
            } else {
                cout << "Not found, please enter something else.\n";
            }
        }
        modifyLineData("data/groups.bk", g->ID() + 1, g->toStr());
        cout << "\t\t--------------------------\t\t\n"
                "\t\t|      1.add word        |\t\t\n"
                "\t\t|      2.edit words      |\t\t\n"
                "\t\t|      3.exit()          |\t\t\n"
                "\t\t--------------------------\t\t\n";
        cout << "Please choose one.\n>>> ";
        cin >> i;
    }
}

//MAINMENU 1 (used to find the groups a word belongs to.
void search() {
    cout << "\t\t--------------------------------\t\t\n"
            "\t\t|     1. search for word.      |\t\t\n"
            "\t\t|     2. search for group.     |\t\t\n"
            "\t\t|     3. exit()                |\t\t\n"
            "\t\t--------------------------------\t\t\n";
    short choice;
    cin >> choice;
    while (choice - 3) {
        if (choice == 1) {
            cout<<"Which way to search? \n 0:name\n 1:meaning\n>>> ";
            int isMeaning;
            cin>>isMeaning;
            errorProcess("Do not write shit.",[](){cout<<"Which way to search? \n 0:name\n 1:meaning\n>>> ";});
            if(isMeaning){
                string mean;
                cout<<"Please enter a meaning.>>> ";
                cin>>mean;
                singWords(searchW([](word* a,const string& flag)->bool{vector<string> m = a->getMean(); return count(m.begin(),m.end(),flag);},mean));
            }else{
                string name;
                cout<<"Please enter a name.>>> ";
                cin>>name;
                singWords(searchW([](word* a, const string& flag)->bool{return a->name == flag;},name));
            }
        } else if (choice == 2) {
            string w;
            cout << "Enter a word in the group, enter # to exit\n>>> ";
            cin >> w;
            while (w != "#") {
                //cout<<endl;
                if (wrds.count(w)) {
                    vector<group *> que;
                    for (group *i : grps) {
                        if (find(i->words.begin(), i->words.end(), wrds[w]) != i->words.end()) {
                            que.push_back(i);
                        }
                    }
                    if (que.empty()) {
                        cout << "This word doesn't belong to any group.\n";
                    } else {
                        groupProfile(que);
                    }
                } else {
                    cout << "Word not found, please check your word bank and enter again.\n";
                }
                cout << "Enter a word in the group, enter # to exit\n>>> ";
                cin >> w;
            }
        } else {
            errorProcess("Please enter valid things.\n", []() {
                cout << "\t\t--------------------------------\t\t\n"
                        "\t\t|     1. search for word.      |\t\t\n"
                        "\t\t|     2. search for group.     |\t\t\n"
                        "\t\t|     3. exit()                |\t\t\n"
                        "\t\t--------------------------------\t\t\n";
            });
        }
        cout << "\t\t--------------------------------\t\t\n"
                "\t\t|     1. search for word.      |\t\t\n"
                "\t\t|     2. search for group.     |\t\t\n"
                "\t\t|     3. exit()                |\t\t\n"
                "\t\t--------------------------------\t\t\n";
        cin>>choice;
    }
}

//MAINMENU2  (new a group.
void newGroup() {
    string flag;
    while (flag != "#") {
        int gFlag;//Determine group category.
        string wd;
        string reason;
        vector<word *> temp;
        cout << "Group by Name or by Meaning? \n0:Meaning\n1:Name\n>>>";
        cin >> gFlag;
        allWord();
        cout << "Please choose words to add. Use # as end.\n>>>";
        cin >> wd;
        while (wd != "#") {
            if (wrds.find(wd) != wrds.end()) {
                temp.push_back(wrds[wd]);
            } else {
                cout << "Word not found. Enter something else.\n";
            }
            cout << ">>>";
            cin >> wd;
        }
        if (!gFlag) {
            cout << "Set group label>>>";
            cin >> reason;
        }
        auto *a = new group(temp, gFlag, reason);
        cout << "Newed group, saving...\n";
        grps.push_back(a);
        group::write(*a);
        cout << "Successful saved group. Enter # to exit.\n";
        cin >> flag;
    }
}

//MAINMENU3 (display all groups
void allGroup() {
    groupProfile(grps);
    cout << "Choose group? Enter x to exit.\n"
            ">>> ";
    char i;
    cin >> i;
    while (i != 'x') {
        int index = (int) (i - '0');
        if (index < grps.size()) {
            newline();
            group::display(*grps[index]);
            newline();
            groupEdit(grps[index]);
        } else {
            cout << "This group does not exist.\n";
        }
        cout << "Choose group? Enter x to exit.\n>>> ";
        cin >> i;
    }
}

//MAINMENU4 (edit word information.
void editWordCard() {
    allWord();
    cout << endl;
    cout << "Please choose which one you'd like to edit, enter # to exit\n>>> ";
    string w;
    cin >> w;
    while (w != "#") {
        if (wrds.count(w)) {
            word::display(wrds[w]);
            editW(wrds[w]);
        } else {
            cout << "Word not found, please check your word bank and enter again.\n";
        }
        cout << "Please choose which one you'd like to edit, enter # to exit\n>>> ";
        cin >> w;
    }
}

//MAINMENU5 (new word construct.
void newWord() {
    string name;
    string temp;
    string example;
    vector<string> meaning;
    cout << "Please enter word name: ";
    cin >> name;
    cout << '\n'
         << "Please enter meanings, using '#' as the end: ";
    while (cin >> temp) {
        if (temp == "#") {
            break;
        }
        meaning.push_back(temp);
    }
    std::cout << '\n'
              << "Please add an example sentence: " << std::endl;
    getchar();
    getline(std::cin, example);
    if (example.empty()) {
        example = "None";
    }
    word *a = new word(name, meaning, example);
    wrds[name] = a;
    word::write(*a);
}