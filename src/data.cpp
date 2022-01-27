//Created by Pedro Barbeira
#include "data.h"



Weight Data::getWeight(const Stop& s1,const Stop& s2){
    double distance = s1.getDistance(s2);
    if(s1.getZone() != s2.getZone())
        return {distance, 1};
    return {distance, 0};
}

//TODO
//Add error checks to file openings
void Data::readStops() {
    int i = 1;
    std::ifstream infile("dataset/stops.csv");
    std::string line;
    std::getline(infile, line);
    while(std::getline(infile, line)){
        std::vector<std::string> data = readCsv(line);
        Stop s(data[0], data[1], data[2], std::stod(data[3]), std::stod(data[4]));
        std::pair<Stop, int> loadPair(s, i);
        stopList.insert(std::pair<string, std::pair<Stop, int>>(s.getCode(), loadPair));
        double key = s.getLatitude() - s.getLongitude();
        stopCoordinates.insert(std::pair<double, string>(key, s.getCode()));
        network.addNode(s.getCode());
        data.clear();
        i++;
    }
    infile.close();
}

void Data::loadLines() {
    auto it = lines.begin();
    std::ifstream infile;
    bool flag = false;
    while(it != lines.end()){
        std::string fileName = "dataset/line_" + it->first;
        if(!flag) fileName += "_0";
        else fileName += "_1";
        fileName += ".csv";
        infile.open(fileName);
        if(!infile.is_open()){
            std::cout << "Error opening " + fileName << endl;
        }
        else{
            std::string from, to;
            std::getline(infile, from);
            std::getline(infile, from);
            while(std::getline(infile, to)){
                std::pair<Stop, int>src = stopList.find(from)->second,
                    dest = stopList.find(to)->second;
                Weight weight = getWeight(src.first, dest.first);
                network.addEdge(src.second, dest.second, it->first, weight);
                from = to;
            }
            if(!flag) flag = true;
            else {
                it++;
                flag = false;
            }
        }
        infile.close();

    }
}

void Data::readLines(){
    std::ifstream infile("dataset/lines.csv");
    std::string line;
    std::getline(infile, line);
    while(std::getline(infile, line)){
        std::vector<string> data = readCsv(line);
        lines.insert(std::pair<string, string>(data[0], data[1]));
        data.clear();
    }
    infile.close();
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