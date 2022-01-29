//Created by Pedro Barbeira
#include "data.h"
#include "Exceptions.h"


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
vector<std::string> Data::getWalkingStops( int n, double maxDist){
    vector<std::string> ret;
    Stop from = network.elementAt(n);
    for(int i = 1; i < network.size(); i++){
        if(i != n){
            Stop to = network.elementAt(i);
            double dist = from.getDistance(to);
            if( dist < maxDist)
                ret.push_back(to.getCode() + "  |  " + to.getName() + "  |  " + to_string(round( dist * 1000 ) ) + " m");
        }
    }
    return ret;
}

void Data::printAllStops(){
    for (auto const &pair: stopList) {
        std::cout << pair.first << " " << pair.second  << "\n";
    }
}

int Data::searchStop(std::string stop){
    auto it = stopList.find(stop);
    if(it == stopList.end())
        return -1;
    else return it->second;
}

void Data::showPath(int src, int dest, typeWeight typeWeight){
    stack<Stop> path;
    try{
        path = network.shortPath(src, dest, typeWeight);
    }catch (NoPathAvailable& e){
        e.printError();
    }

    while (path.size() != 1){
        cout << path.top().getName() << " -> ";
        path.pop();
    }
    cout << path.top().getName() << endl;
}