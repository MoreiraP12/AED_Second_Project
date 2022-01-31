#include "input.h"

using namespace std;

namespace input {
    string getRaw() {
        std::string str;
        std::cout << "> ";
        std::getline(std::cin, str);
        trimString(str);
        std::cout << std::endl;
        return str;
    }

    void waitEnter() {
        std::cout << std::endl << "Press enter to continue..." << std::endl;
        std::string str;
        std::getline(std::cin, str);
    }

    void trimString(std::string &str) {
        auto front = std::find_if_not(str.begin(), str.end(), [](int c) {
            return std::isspace(c);
        });
        auto back = std::find_if_not(str.rbegin(), str.rend(), [](int c) {
            return std::isspace(c);
        }).base();
        str = back <= front ? std::string() : std::string(front, back);

        auto new_end = std::unique(str.begin(), str.end(), [](char a, char b) {
            return (a == b) && (a == ' ');
        });
        str.erase(new_end, str.end());
    }

    bool validateStop(Data* data, const std::string& stop){
        return data->searchStop(stop) != -1;
    }

    bool validateStop(Data* data, const double& longitude, const double& latitude){
        return data->searchStop(longitude,  latitude) != -1;
    }

    int stringToInt(Data* data,const std::string& stop){
        return data->searchStop(stop);
    }

    int coordsToInt(Data* data,const double& longitude, const double& latitude){
        return data->searchStop(longitude, latitude);
    }
}