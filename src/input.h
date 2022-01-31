#ifndef AED_PROJ1_INPUT_H
#define AED_PROJ1_INPUT_H


#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "data.h"

using namespace std;

namespace input {
    /**
     * Get a string from cin
     * @return string
     */
    string getRaw();


    /**
     * Convert a string to a var of type T
     * @tparam T - Type with defined >> operator
     * @param str - String to be read
     * @param var - Output after reading
     * @return true if operation was successful
     */
    template<typename T>
    bool strToVar(const string &str, T &var) {
        istringstream ss{str};
        ss >> var;
        if (ss.fail() || !ss.eof()) {
            return false;
        }
        return true;
    }

    /**
     * Get a var of type T from cin
     * @tparam T - Type with defined >> operator
     * @param var - Output
     * @return true if operation was successful
     */
    template<typename T>
    bool get(T &var) {
        string str = getRaw();
        if (str.empty()) {
            return false;
        }
        return strToVar(str, var);
    }

    /**
     * Wait for user to press enter
     */
    void waitEnter();

    void trimString(string &str);
    /**
     * Check if name is valid
     * @param name
     * @return true if valid
     */

    /**
     * Checks for the existence of inputted stop id string
     * @return true if exists in our 'database'
     */
    bool validateStop(Data* data,const std::string& stop);

    /**
     * Checks for the existence of inputted stop id string
     * @return true if exists in our 'database'
     */
    bool validateStop(Data* data,const double& longitude,const double& latitude);

    /**
     * Transforms string stop inputs into their relative position in the graph
     * @param data our singleton graph
     * @param stop
     * @return the int - relative position in the graph
     */
    int stringToInt(Data* data,const std::string& stop);

    /**
     * Transforms coordinates inputs into their relative position in the graph
     * @param data our singleton graph
     * @param longitude longitude
      * @param latitude latitude
     * @return the int - relative position in the graph
     */
    int coordsToInt(Data* data,const double& longitude, const double& latitude);

}

#endif //AED_PROJ1_INPUT_H
