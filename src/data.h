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
public:

    Data(){
        network = Graph();
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

    Stop findStop(std::string stop);





    string elementAt(int i){
        return network.elementAt(i);
    }

    int graphSize() {
        return network.size();
    }

    void edgesAt(int i){
        network.printEdges(i);
    }

    void linesAt(int i){
        network.printLines(i);
    }

};


#endif //AED_PROJ_2_DATA_H
