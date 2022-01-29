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
    cout << "Main Menu:\n\n";
    cout << "[" << ++options << "] " << "All Stops\n";
    cout << "[" << ++options << "] " << "Stops near me\n";
    cout << "[" << ++options << "] " << "Origin -> Destination\n";
    cout << "[0] Exit\n";
}

Menu * MainMenu::getNextMenu() {
    int option;
    if(!input::get(option)){
        return invalidOption();
    }
    switch(option){
        case 0: return nullptr;
        case 1: return new AllStopsMenu();
        case 2: return new NearbyStopsMenu();
        case 3: return new SearchMenu();
    }
    return invalidOption();
}

// ---------------  Stops Menu ---------------
AllStopsMenu::AllStopsMenu() : Menu() {}
void AllStopsMenu::show() {
    system("cls");
    data->printAllStops();

}
Menu * AllStopsMenu::getNextMenu() {
    input::waitEnter();
    return nullptr ;
}

// ---------------  Nearby Stops Menu ---------------
NearbyStopsMenu::NearbyStopsMenu() : Menu() {}
void NearbyStopsMenu::show() {
    system("cls");
    cout << "Please tell us in which station you're and how much you're willing to walk" << endl;

}
Menu * NearbyStopsMenu::getNextMenu() {
    string origin;
    double distance;

    cout << " Origin\n ";
    if(!input::get(origin)){
        return invalidOption();
    }

    cout << " Distance\n ";
    if(!input::get(distance)){
        return invalidOption();
    }

    vector<string> stops = data->getWalkingStops(17, 1.0);

    for(auto x:  stops){
        cout << x << endl;
    }
    input::waitEnter();


    return nullptr ;
}


// ---------------  Search Stops Menu ---------------
SearchMenu::SearchMenu() : Menu() {}
void SearchMenu::show() {
    system("cls");
    cout << "Please tell us in which station you're and where you want to go" << endl;
    cout << "You'll also be presented with the different option to you're preferred search method" << endl;

}
Menu * SearchMenu::getNextMenu() {
    string origin, destination;
    bool walk;
    double distance;

    cout << " Origin\n ";
    if(!input::get(origin) || !input::validateStop(data,origin)){
        return invalidOption();
    }

    cout << " Destination\n ";
    if(!input::get(destination ) || !input::validateStop(data,origin)){
        return invalidOption();
    }

    cout << " Walk (Yes: 1 | No: 0) \n ";
    if(!input::get(walk )){
        return invalidOption();
    }

    cout << " Distance \n ";
    if(!input::get(distance)){
        return invalidOption();
    }

    unsigned int options = 0;
    system("cmd /c cls");
    cout << "Main Menu:\n\n";
    cout << "[" << ++options << "] " << "Minimum Stops\n";
    cout << "[" << ++options << "] " << "Minimum Distance\n";
    cout << "[" << ++options << "] " << "Minimum Line Changes\n";
    cout << "[" << ++options << "] " << "Cheaper\n";

    int option;
    if(!input::get(option)){
        return invalidOption();
    }
    if(walk){data->injectWalkingEdges(distance);}
    switch(option){
        case 1: data->minStops(input::stringToInt(data,origin), input::stringToInt(data,destination));
        //TODO;
    }
    if(walk){data->deleteWalkingEdges();}

    input::waitEnter();
    return nullptr;
}

