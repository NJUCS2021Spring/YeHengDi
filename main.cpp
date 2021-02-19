#include <iostream>
#include <map>
#include "templates.h"
#include "tools.h"

using namespace std;
static map<string, word> WordBank;
static vector<group> Groups;

int main()
{
    word test = newWord();

    if (load() == -1)
    {
        cout << "Failed to load.\n";
        return -1;
    }
}
