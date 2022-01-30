#include "src/Menu.h"
#include <stack>
#include <iomanip>

int main() {

    Data* data = new Data();

    std::stack<Menu *> menus;
    menus.push(new MainMenu(data));

    while(!menus.empty()){
        menus.top()->show();
        Menu * ptr = menus.top()->getNextMenu();
        if(ptr){
            if(ptr != menus.top()){
                menus.push(ptr);
            }
        }
        else{
            delete menus.top();
            menus.pop();
        }
    }
    return 0;
}
