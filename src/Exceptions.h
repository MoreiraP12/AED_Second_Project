#ifndef AED_PROJ_2_EXCEPTIONS_H
#define AED_PROJ_2_EXCEPTIONS_H

#include "Stop.h"

class NoPathAvailable: public std::exception{
public:
    NoPathAvailable()= default;
    void printError(){
        std::cout << "There are no available stops to reach your destination" << std::endl;
    }
};

#endif
