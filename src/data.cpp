//Created by Pedro Barbeira
#include "data.h"

void Data::readStops() {
    std::vector<Stop*> stops;
    std::ifstream infile("dataset/stops.csv");
    std::string line;
    std::getline(infile, line);
    while(std::getline(infile, line)){
        std::vector<std::string> data = readCsv(line);
        Stop* s = new Stop(data[0], data[1], data[2], std::stod(data[3]), std::stod(data[4]));
        stops.push_back(s);
    }
}

std::vector<std::string> Data::readCsv(std::string line) {
    int i;
    std::string load;
    std::vector<std::string> ret;
    while(!line.empty()){
        i = line.find(',');
        if(i == std::string::npos){
            load = line;
            line.clear();
        }
        else {
            load = line.substr(0, i);
            line = line.substr(i+1);
        }
        ret.push_back(load);
    }
    return ret;
}