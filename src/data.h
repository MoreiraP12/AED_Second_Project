//Created by Pedro Barbeira
#ifndef AED_PROJ_2_DATA_H
#define AED_PROJ_2_DATA_H

#include <unordered_map>
#include "stop.h"
#include <vector>
#include <fstream>
#include "graph.h"

class Data {
    std::unordered_map<std::string, int> stopList;
    std::unordered_map<double, int> stopCoordinates;
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

    Stop findStop(std::string stop);

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

    int graphSize() {
        return network.size();
    }

    void showPath(int src, int dest, typeWeight typeWeight){//TODO melhorar a apresentação
        stack<Stop> path = network.shortPathDijkstra(src,dest,typeWeight);
        while (path.size() != 1){
            cout << path.top().getName() << " -> ";
            path.pop();
        }
        cout << path.top().getName() << endl;
    }

};


#endif //AED_PROJ_2_DATA_H
