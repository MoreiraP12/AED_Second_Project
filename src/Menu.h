#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <set>
#include <algorithm>

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

    Menu * invalidOption();
public:
    explicit Menu();
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
    explicit MainMenu();
    ~MainMenu() override;
    void show() override;
    Menu * getNextMenu() override;
};

class MinimumStopsMenu : public Menu{
public:
    explicit MinimumStopsMenu();
    void show() override;
    Menu * getNextMenu() override;
};

class MinimumStopsAlgorithmMenu : public Menu{
public:
    explicit MinimumStopsAlgorithmMenu();
    void show() override;
    Menu * getNextMenu() override;
};