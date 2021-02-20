#include <iostream>
#include "dataStruct.cpp"

int main() {
    group testg;
    std::string name;
    for(int i:{1,2,3,4,5}){
        std::cin>>name;
        testg.addMember(word(name));
    }
    group::display(testg);
    group::write(testg);
}
