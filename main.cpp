#include <iostream>
#include "process.h"
using namespace std;

int main() {
    load();
    mainMenu();
    vector<void(*)()> funcs = {search, newGroup, allGroup, editWordCard, newWord};
    int i;
    cin>>i;
    while(true){
        /*while(cin.fail()){
            cout<<"Please do not enter shit.\n";
            cin.clear();
            cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
            mainMenu();
            cin>>i;
        }*/
        if(i<=5 && i>=1) {
            funcs[i - 1]();
            mainMenu();
            cin>>i;
        }else if (i == 6){
            return 0;
        }else{
            errorProcess("Please do not enter shit.", mainMenu);
            cin>>i;
        }
    }
}
