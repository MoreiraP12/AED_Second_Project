//Created by Pedro Barbeira
#ifndef AED_PROJ_2_DATA_H
#define AED_PROJ_2_DATA_H

#include <unordered_map>
#include "Stop.h"
#include <vector>
#include <fstream>
#include <iomanip>
#include "Exceptions.h"
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
    std::vector<std::string> static readCsv(std::string line);

    /**
     * Returns the weight of the edge that connects two stops
     * @param s1 the first stop
     * @param s2 the second stop
     * @return the weight of the edge that connects them
     */
    Weight static getWeight(const Stop& s1,const Stop& s2);

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

public:

    /**
     * Constructor for Data class. Reads the dataset files and loads them
     * into the system using the private methods. Handles exceptions in
     * case a file doesn't open;
     */
    Data(){
        network = Graph();
        try {
            this->readStops();
            this->readLines();
            this->loadLines();
        }
        catch(ErrorOpeningInfile& e){
            e.print();
        }
    }

    /**
     * Prints all the stops stored in hashtable for user convenience
     */
    void printAllStops();


    /**
     * Searches for the existence of received stop
     * in order to validate inputs
     * @return the index of the id, if it exists; -1 otherwise
     */
    int searchStop(const std::string&);

    /**
     * Shows the shortest path between two stops according to the desired
     * weight parameter
     * @param src the source node
     * @param dest the destination node
     * @param typeWeight the weight parameter
     */
    void showWalkingStops(int i, double distance);

    /**
     * Indejcts edges between stops that are below a certain walking distance,
     * @param maxDist the maximum distance between two stops
     */
    void injectWalkingEdges(double maxDist){
        network.createWalkingEdges(maxDist);
    }

    /**
     * Removes from the graph "walking'
     */
    void deleteWalkingEdges(){
        network.destroyWalkingEdges();
    }


    vector<std::pair<Stop, double>> getWalkingStops( int n, double maxDist);

    /**
     * Prints the path between two stops, depending on user input. Allows for
     * different search paramters
     * @param src the source Stop
     * @param dest the destination Stop
     * @param typeWeight the search parameter
     */
    void showPath(int src, int dest, typeWeight typeWeight);

};


#endif //AED_PROJ_2_DATA_H
