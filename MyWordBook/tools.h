#include <fstream>
#include <vector>
#include "templates.h"
#ifndef MYWORDBOOK_TOOLS_H
#define MYWORDBOOK_TOOLS_H
using namespace std;
word newWord()
{
    word baby;
    string name;
    cout << "Please enter word name: ";
    cin >> name;
    baby.name = name;
    cout << '\n'
         << "Please enter meanings, using '#' as the end: ";
    while (cin >> name)
    {
        if (name == "#")
        {
            break;
        }
        baby.meaning.push_back(name);
    }
    cout << '\n'
         << "Please add an example sentence: " << endl;
    getchar();
    getline(cin, name);
    baby.example = name;
    return baby;
}

word newWord(string name, vector<string> meaning, string example)
{
    word baby;
    baby.name = name, baby.meaning = meaning, baby.example = example;
    return baby;
}

group newGroup(){
    
}
//load 还没写完.
int load()
{
    std::ifstream wrd, grp;
    wrd.open("words.w");
    grp.open("groups.w");
    if (!wrd)
    {
        return -1;
    }

    return 0;
}

void write(word wrd)
{
    std::ofstream w;
    w.open("words.w", ios::app);
    string meaning = "";
    for (string i : wrd.meaning)
    {
        meaning.append((i + ';'));
    }
    w << wrd.name << "/" << meaning << "/" << wrd.example << "\n";
    w.close();
}

void write(group grp)
{
    std::ofstream g;
    g.open("groups.w", ios::app);
    g << grp.ID << '/';
    for (string i : grp.words)
    {
        g << i <<'/';
    }
    if (!grp.isShape){
        g<<grp.reason<<"\n";
    }
    g.close();
}

void add(word wrd)
{
    if (!WordBank.count(wrd.name))
    {
        WordBank[wrd.name] = wrd;
        write(wrd);
        cout << "Succeed!\n";
    }
    else
    {
        cout << "This word already exists in wordbank.\n";
    }
}


#endif //MYWORDBOOK_TOOLS_H
