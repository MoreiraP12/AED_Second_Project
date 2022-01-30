#ifndef AED_PROJ_2_EXCEPTIONS_H
#define AED_PROJ_2_EXCEPTIONS_H

#include "Stop.h"

/**
 * Exception class for when there is no path between stops a and b
 */
class NoPathAvailable: public std::exception{
public:
    /**
     * Default constructor
     */
    NoPathAvailable()= default;

    /**
     * Informs the user that there is no path between his desired stops
     */
    void static printError(){
        std::cout << "There are no available stops to reach your destination" << std::endl;
    }
};


/**
 * Exception class for when there's an error opening input files
 */
class ErrorOpeningInfile : public std::exception{
    std::string fileName;
public:
    /**
     * Constructor for the exception class. Receives the name of the file
     * that caused the error as parameter
     * @param name the name of the file
     */
    explicit ErrorOpeningInfile(std::string name) : fileName(name){};

    /**
     * Informs the user there was an error opening input file "fileName"
     */
    void print() {
        std::cout << "Error opening input file " << fileName <<"\n";
    }
};

#endif
