#include "menu.h"

using namespace std;

Menu * Menu::invalidOption() {
    cout << "Invalid option" << std::endl;
    input::waitEnter();

    return this;
}

// --------------- Main Menu ---------------

MainMenu::~MainMenu(){
    delete data;
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
        case 1: return new AllStopsMenu(data);
        case 2: return new NearbyStopsMenu(data);
        case 3: return new SearchMenu(data);
        default: return nullptr;
    }
}

// ---------------  Stops Menu ---------------
void AllStopsMenu::show() {
    system("cls");
    data->printAllStops();

}
Menu * AllStopsMenu::getNextMenu() {
    input::waitEnter();
    return nullptr ;
}

// ---------------  Nearby Stops Menu ---------------
void NearbyStopsMenu::show() {
    system("cls");
    cout << "Please tell us in which station or coordinates you're and how much you're willing to walk" << endl;

}
Menu * NearbyStopsMenu::getNextMenu() {
    double distance;
    cout << " Distance (km)\n\n ";
    if(!input::get(distance)){
        return invalidOption();
    }

    unsigned int options = 0;
    cout << "Search Options:\n\n";
    cout << "[" << ++options << "] " << "Name Stop\n";
    cout << "[" << ++options << "] " << "Coordinates\n";
    int option;
    if(!input::get(option)){
        return invalidOption();
    }

    switch (option) {
        case 1:
        {
            string origin;
            cout << " Origin\n ";
            if(!input::get(origin)){
                return invalidOption();
            }
            system("cls");
            cout << "Stops:" << std::endl;
            data->showWalkingStops(input::stringToInt(data,origin), distance);
            break;
        }
        case 2:
        {
            double originLatitude, originLongitude;
            cout << "Origin - Longitude";
            if(!input::get(originLongitude))
                return invalidOption();
            cout << "Origin - Latitude";
            if(!input::get(originLatitude))
                return invalidOption();
            system("cls");
            cout << "Stops:" << std::endl;
            data->showWalkingStops(originLongitude,originLatitude, distance);
            break;
        }
        default:{
            break;
        }
    }

    input::waitEnter();
    return nullptr ;
}


// ---------------  Search Stops Menu ---------------
void SearchMenu::show() {
    system("cls");
    cout << "Please tell us in which station you're and where you want to go" << endl;
    cout << "You'll also be presented with the different option to you're preferred search method" << endl;

}
Menu * SearchMenu::getNextMenu() {
    int originNode, destinationNode;
    bool walk;
    double distance;

    unsigned int options = 0;
    cout << "Search Options:\n\n";
    cout << "[" << ++options << "] " << "Name\n";
    cout << "[" << ++options << "] " << "Coordinates\n";
    int option;
    if(!input::get(option)){
        return invalidOption();
    }

    switch(option){
        case 1:{
            string origin, destination;
            cout << " Origin\n ";
            if(!input::get(origin) || !input::validateStop(data,origin)){
                return invalidOption();
            }

            cout << " Destination\n ";
            if(!input::get(destination ) || !input::validateStop(data,destination)){
                return invalidOption();
            }
            originNode = input::stringToInt(data,origin);
            destinationNode = input::stringToInt(data,destination);
            break;
        }

        case 2:{
            double originLatitude, originLongitude, destinationLatitude, destinationLongitude;
            cout << "Origin - Longitude";
            if(!input::get(originLongitude))
                return invalidOption();
            cout << "Origin - Latitude";
            if(!input::get(originLatitude))
                return invalidOption();
            if(!input::validateStop(data, originLongitude, originLatitude))
                return invalidOption();

            cout << "Destination - Longitude";
            if(!input::get(destinationLongitude))
                return invalidOption();
            cout << "Origin - Latitude";
            if(!input::get(destinationLatitude))
                return invalidOption();
            if(!input::validateStop(data, destinationLongitude, destinationLatitude))
                return invalidOption();

            originNode = input::coordsToInt(data, originLongitude, originLatitude);
            destinationNode = input::coordsToInt(data, destinationLongitude, destinationLatitude);
            break;
        }
        default:{
            break;
        }
    }

    cout << " Walk (Yes: 1 | No: 0) \n ";
    if(!input::get(walk )){
        return invalidOption();
    }

    if(walk){
        cout << " Distance(km) \n ";
        if(!input::get(distance)){
            return invalidOption();
        }
    }

    options = 0;
    system("cmd /c cls");
    cout << "Path Options:\n\n";
    cout << "[" << ++options << "] " << "Minimum Stops\n";
    cout << "[" << ++options << "] " << "Minimum Distance\n";
    cout << "[" << ++options << "] " << "Minimum Line Changes\n";
    cout << "[" << ++options << "] " << "Cheaper\n";
    if(!input::get(option)){
        return invalidOption();
    }

    system("cmd /c cls");
    cout << "|Options|" << std::endl;
    if(walk){
        cout << "Walk: Yes" << "| Distance(km) : " << distance << std::endl;
    }else{
        cout << "Walk: No" << std::endl;
    }

    if(walk){data->injectWalkingEdges(distance);}
    cout << "Path: " << std::endl;
    switch(option){
        case 1:
            data->showPath(originNode,destinationNode , STOPS);
            break;
        case 2:
            data->showPath(originNode,destinationNode, DIST);
            break;
        case 3:
            data->showPath(originNode,destinationNode, LINE);
            break;
        case 4:
            data->showPath(originNode,destinationNode, ZONE);
            break;
        default: break;
    }
    if(walk){data->deleteWalkingEdges();}

    input::waitEnter();
    return nullptr;
}

