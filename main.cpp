#include <iostream>
#include "process.h"
using namespace std;

int main() {
    load();
    mainMenu();
    vector<void(*)()> funcs = {checkGroupWord, newGroup, allGroup, editWordCard, newWord};
    int i;
    while(cin>>i){
        if(i<=5 && i>=1) {
            funcs[i - 1]();
        }else if (i == 6){
            return 0;
        }else{
            cout<<"Please enter valid number.\n";
        }
        cout<<">>> ";
    }
}
