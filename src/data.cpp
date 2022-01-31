#include "data.h"


Weight Data::getWeight(const Stop& s1,const Stop& s2){
    double distance = s1.getDistance(s2);
    if(s1.getZone() != s2.getZone())
        return {distance, 1};
    return {distance, 0};
}

void Data::readStops() {
    int i = 1;
    std::ifstream infile("dataset/stops.csv");
    if(!infile.is_open()){
        throw ErrorOpeningInfile((string &) "stops.csv");
    }
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
            throw ErrorOpeningInfile(fileName);
        }
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
    if(!infile.is_open()){
        throw ErrorOpeningInfile((string &) "lines.csv");
    }
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
    unsigned long long i;
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

set<std::pair<Stop, double>> Data::getWalkingStops(int n, double maxDist){
    set<pair<Stop, double>> ret;
    Stop from = network.elementAt(n);
    for(int i = 1; i <= network.size(); i++){
        if(i == n) continue;
        Stop to = network.elementAt(i);
        double dist = from.getDistance(to);
        if( dist < maxDist)
            ret.insert({to,dist});
    }
    return ret;
}

set<std::pair<Stop, double>> Data::getWalkingStops(double longitude, double latitude, double maxDist){
    set<pair<Stop, double>> ret;
    Stop from = Stop("","","",longitude, latitude);
    for(int i = 1; i <= network.size(); i++){
        Stop to = network.elementAt(i);
        double dist = from.getDistance(to);
        if( dist < maxDist)
            ret.insert({to,dist});
    }
    return ret;
}

void Data::printAllStops(){
    cout << std::setw(35) << "Name" << std::setw(35) << "Code" << std::setw(35) << "Zone" << std::endl;
    for (auto const &pair: stopList) {
        Stop stop = network.elementAt(pair.second);
        cout << std::setw(35) << stop.getName() << std::setw(35) << stop.getCode() << std::setw(35) << stop.getZone() << std::endl;
    }
}

int Data::searchStop(const std::string& stop){
    auto it = stopList.find(stop);
    if(it == stopList.end())
        return -1;
    else return it->second;
}

int Data::searchStop(const double& longitude, const double& latitude){
    auto it = stopCoordinates.find(longitude-latitude);
    if(it == stopCoordinates.end())
        return -1;
    else return it->second;
}

void Data::showPath(int src, int dest, typeWeight typeWeight){
    stack<ShowStop> path;
    try{
        path = network.shortPath(src, dest, typeWeight);
    }catch (NoPathAvailable& e){
        NoPathAvailable::printError();
    }

    cout << std::setw(35) << "Name" << std::setw(10) << "Code" << std::setw(10) << "Zone"  << std::setw(20) << "NextLine" << std::endl;
    while (!path.empty()){
        cout << std::setw(35) << path.top().stop.getName() << std::setw(10) << path.top().stop.getCode() << std::setw(10) << path.top().stop.getZone() << setw(17);
        auto it = path.top().lines.begin();
        cout << *it;
        it++;
        while(it != path.top().lines.end()){
            cout << "/" << *it ;
            it++;
        }
        cout << endl;
        path.pop();
    }
}

bool operator<(const pair<Stop, double>& p1, const pair<Stop, double>& p2){
    return p1.second < p2.second;
}

void Data::showWalkingStops(int i, double distance) {
    set<pair<Stop, double>> stops = getWalkingStops(i,distance);
    auto it = stops.begin();
    cout << std::setw(35) << "Name" << std::setw(17) << "Code" << std::setw(17) << "Zone" << std::setw(20) << "Distance(meters)" << std::endl;
    while (it != stops.end()){
        cout << std::setw(35) << it->first.getName() << std::setw(17) << it->first.getCode() << std::setw(17) << it->first.getZone() << std::setw(20) << round(it->second*1000) << std::endl;
        it++;
    }
}

void Data::showWalkingStops(double longitude, double latitude, double distance) {
    set<pair<Stop, double>> stops = getWalkingStops( longitude,  latitude,distance);
    auto it = stops.begin();
    cout << std::setw(35) << "Name" << std::setw(17) << "Code" << std::setw(17) << "Zone" << std::setw(20) << "Distance(meters)" << std::endl;
    while (it != stops.end()){
        cout << std::setw(35) << it->first.getName() << std::setw(17) << it->first.getCode() << std::setw(17) << it->first.getZone() << std::setw(20) << round(it->second*1000) << std::endl;
        it++;
    }
}