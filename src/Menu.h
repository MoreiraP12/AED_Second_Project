#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <set>
#include <algorithm>
#include "data.h"

using namespace std;
/**
 * a Menu that bases its implementation on a stack
 *
 * Every menu has two methods:
 * show() - responsible for the "view" in the console, provides useful messages to the user or important info in text form
 * getNextMenu() - responsible for the behaviour aspect of the program, receives inputs and returns the new path in form of a pointer
 */
class Menu{
protected:
    Data* data;
    Menu * invalidOption();
public:
    explicit Menu(Data* d) : data(d){};
    virtual ~Menu() = default;
    /**
     * Show information associated with the menu
     */
    virtual void show() = 0;
    /**
     * Return a pointer to the next menu ('nullptr' and 'this' can also be returned)
     * nullptr -> Return to previous menu
     * this -> Don't change the menu
     * @return Menu * to next menu
     */
    virtual Menu * getNextMenu() = 0;
};

/**
 * Displays all possible paths from login in to partial listings of flights andd transports
 */
class MainMenu : public Menu {
public:
    explicit MainMenu(Data* d) : Menu(d){};
    ~MainMenu() override;
    void show() override;
    Menu * getNextMenu() override;
};
/**
 * Total listing of stops
 *
 * Useful for our user to make know which stops exits and to which stop he might want to go
 */
class AllStopsMenu : public Menu{
public:
    explicit AllStopsMenu(Data* d) : Menu(d){};
    void show() override;
    Menu * getNextMenu() override;
};
/**
 * Partial listing of stops
 *
 * Displays all the stops near you
 * How near you want it to be is solely determined by you
 */
class NearbyStopsMenu : public Menu{
public:
    explicit NearbyStopsMenu(Data* d) : Menu(d){};
    void show() override;
    Menu * getNextMenu() override;
};

/**
 * Search the best path according to user requests
 *
 * Displays the best path to get to a desired destination
 */
class SearchMenu : public Menu{
public:
    explicit SearchMenu(Data* d) : Menu(d){};
    void show() override;
    Menu * getNextMenu() override;
};




