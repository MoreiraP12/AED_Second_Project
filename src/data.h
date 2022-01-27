//Created by Pedro Barbeira
#ifndef AED_PROJ_2_DATA_H
#define AED_PROJ_2_DATA_H

#include <unordered_map>
#include "stop.h"
#include <vector>
#include <fstream>
#include "graph.h"

class Data {
    std::unordered_map<std::string, std::pair<Stop, int>> stopList;
    std::unordered_map<double, std::string> stopCoordinates;
    std::unordered_map<string, string> lines;
    Graph network;

    /**
     * Breaks up a line in .csv format into a vector of strings
     * @param line the .csv line to be broken up
     * @return a vector with each field of the .csv line
     */
    std::vector<std::string> readCsv(std::string line);

    Weight getWeight(const Stop& s1,const Stop& s2);

public:

    Data(){
        network = Graph();
        this->readStops();
        this->readLines();
        this->loadLines();
    }

    /**
     * Reads and parses stops from the stops.csv file and saves them in
     * the system.
     */
    void readStops();

    /**
     * Reads and parses lines from lines.csv file and saves them in the
     * system
     */
    void readLines();

    /**
     * Iterated through the lines map, accessing each individual line file
     * in order to load the edges of the network graph
     * Time Complexity: O(n * m) where n is the number of files and m is the
     * average of the number of lines in each file
     */
    void loadLines();

<<<<<<< HEAD
    /**
     * Prints all the stops stored in hashtable for user convenience
     */
    void printStops();

    /**
     * Searches for the existence of received stop
     * in order to validate inputs
     * @return true if the received stop id exists
     */
    bool searchStop(std::string);



=======
>>>>>>> d4fcd445b2dd090e9e972d382bf58b4f43eb7140
    string elementAt(int i){
        return network.elementAt(i);
    }

    int graphSize() {
        return network.size();
    }

<<<<<<< HEAD
    void edgesAt(int i){
        network.printEdges(i);
    }

    void linesAt(int i){
        network.printLines(i);
    }


=======
>>>>>>> d4fcd445b2dd090e9e972d382bf58b4f43eb7140
};


#endif //AED_PROJ_2_DATA_H
