#include "Menu.h"
#include "Input.h"
#include "data.h"

using namespace std;

Data* Menu::data= new Data();

Menu::Menu() {
}

Menu * Menu::invalidOption() {
    cout << "Invalid option" << std::endl;
    input::waitEnter();

    return this;
}

// --------------- Main Menu ---------------
MainMenu::MainMenu():Menu(){}

MainMenu::~MainMenu(){
    //save the data to the .csv

}

void MainMenu::show() {

    unsigned int options = 0;
    system("cmd /c cls");
    data->showPath(8,10, dist);
    //data->showPath(8,10, zone);
    cout << "Main Menu:\n\n";
    cout << "[" << ++options << "] " << "All Stops\n";
    cout << "[" << ++options << "] " << "Minimum Amount of Stops\n";
    cout << "[0] Exit\n";
}

Menu * MainMenu::getNextMenu() {
    int option;
    if(!input::get(option)){
        return invalidOption();
    }
    switch(option){
        case 0: return nullptr;
        case 1: return new StopsMenu();
        case 2: return new MinimumStopsMenu();
    }
    return invalidOption();
}

// ---------------  Stops Menu ---------------
StopsMenu::StopsMenu() : Menu() {}
void StopsMenu::show() {
    system("cls");
    //data->printStops(); //TODO

}
Menu * StopsMenu::getNextMenu() {
    input::waitEnter();
    return nullptr ;
}


// --------------- Minimum Stops Menu ---------------
MinimumStopsMenu::MinimumStopsMenu() : Menu() {}
void MinimumStopsMenu::show() {
    system("cls");
    cout << "\n Please tells us in which station you're and where you want go!\n \n";
}
Menu * MinimumStopsMenu::getNextMenu() {
    string origin, destination;

    cout << " Origin\n ";
    if(!input::get(origin) || !input::validateStop(data,origin)){
        return invalidOption();
    }

    cout << " Destination\n ";
    if(!input::get(destination ) || !input::validateStop(data,origin)){
        return invalidOption();
    }

    input::waitEnter();
    return new MinimumStopsAlgorithmMenu() ;
}

//  --------------- Minimum Stops Algorithm Menu ---------------

MinimumStopsAlgorithmMenu::MinimumStopsAlgorithmMenu() : Menu() {}
void MinimumStopsAlgorithmMenu::show() {
    system("cls");
    //Here should be the chain of minimum stops for the desired path (call)
    int options;
    cout << "Main Menu:\n\n";
    cout << "[" << ++options << "] " << "Back\n";

}
Menu * MinimumStopsAlgorithmMenu::getNextMenu() {
    int option;
    if(!input::get(option)){
        return invalidOption();
    }
    switch(option){
        case 1: return nullptr;
    }
    return invalidOption();
}
