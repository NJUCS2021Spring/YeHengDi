#include <iostream>
#include <vector>

#ifndef MYWORDBOOK_UITLS_H
#define MYWORDBOOK_UITLS_H
/*词结构体*/
typedef struct word
{
    std::string name = "无";
    std::string example = "无";
    std::vector<std::string> meaning;
} word;
/*组结构体*/
typedef struct group
{
    int ID = 0;
    std::vector<string> words;
    bool isShape = false;
    string reason = "NoReason";
} group;

#endif //MYWORDBOOK_UITLS_H
