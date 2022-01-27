#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include "stop.h"

using namespace std;

struct Weight{
    double distance;
    int zone;
};

struct Edge {
    int dest;
    std::list<std::string> lines;
    Weight weight;
};

struct Node {
    list<Edge> adj;
    int distance;
    bool visited;
    std::string stop;
    std::string parent;
};

class Graph {
    int n;
    bool hasDir;
    vector<Node> nodes;

public:
    Graph();
    void addNode(std::string s);
    void addEdge(int src, int dest, std::string line, Weight weight);
    string elementAt(int i){
        return nodes[i].stop;
    }
    int size(){
        return nodes.size();
    }
};

#endif
