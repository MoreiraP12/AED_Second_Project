#include "Menu.h"
#include "Input.h"

using namespace std;

Menu::Menu() {}

Menu * Menu::invalidOption() {
    cout << "Invalid option" << std::endl;
    input::waitEnter();

    return this;
}

// --------------- Main Menu ---------------
MainMenu::MainMenu():Menu(){
    //populate all the data to the multiple graphs
}

MainMenu::~MainMenu(){
    //save the data to the .csv

}

void MainMenu::show() {
    unsigned int options = 0;

    system("cmd /c cls");
    cout << "Main Menu:\n\n";
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
        case 1: return new MinimumStopsMenu();
    }
    return invalidOption();
}

// --------------- Minimum Stops Menu ---------------
MinimumStopsMenu::MinimumStopsMenu() : Menu() {}
void MinimumStopsMenu::show() {
    system("cls");
    cout << "\n Please tells us in which station you're and where you want go!\n";
}
Menu * MinimumStopsMenu::getNextMenu() {
    string origin, destination;

    cout << "origin\n ";
    if(!input::get(origin)){
        //there should be some kind of input validation that tells me if the station exists and/or if I'm inputting invalid stuff(nothing, only special characters, etc...)
        return invalidOption();
    }

    cout << "destination\n ";
    if(!input::get(destination)){
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
    cout << "[" << ++options << "] " << "Home\n";
    cout << "[" << ++options << "] " << "Back\n";

}
Menu * MinimumStopsAlgorithmMenu::getNextMenu() {
    int option;
    if(!input::get(option)){
        return invalidOption();
    }
    switch(option){
        case 1: return new MainMenu();
        case 2: return nullptr;
    }
    return invalidOption();
}

