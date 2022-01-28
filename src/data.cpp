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
        stopList.insert({s.getCode(),i});
        double key = s.getLatitude() - s.getLongitude();
        stopCoordinates.insert({abs(key),i});
        network.addNode(s);
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
                int src = stopList.find(from)->second, dest = stopList.find(to)->second;
                Weight weight = getWeight(network.elementAt(src), network.elementAt(dest));//TODO
                network.addEdge(src, dest, it->first, weight);
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

/*
>>>>>>> 3ad4ca56dbd3e2b1c471f703c7a139df7b30fce4
void Data::printStops(){
    for (auto const &pair: stopList) {
        std::cout << pair.first << " " << pair.second.first.getName() << " " << pair.second.first.getZone() << "\n";
    }

}*/

bool Data::searchStop(std::string stop){
    return stopList.find(stop) != stopList.end();

}