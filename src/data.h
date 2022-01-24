//Created by Pedro Barbeira
#ifndef AED_PROJ_2_DATA_H
#define AED_PROJ_2_DATA_H

#include <map>
#include "stop.h"
#include <vector>
#include <fstream>

class Data {
    std::map<std::string, int> stoplist;
    std::vector<Stop*> stops;
public:

    /**
     * Reads and parses stops from the stops.csv file
     */
    void readStops();


    /**
     * Breaks up a line in .csv format into a vector of strings
     * @param line the .csv line to be broken up
     * @return a vector with each field of the .csv line
     */
    std::vector<std::string> readCsv(std::string line);
};


#endif //AED_PROJ_2_DATA_H
