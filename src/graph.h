#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include "stop.h"
#define INF (INT_MAX/2)

using namespace std;

enum typeWeight{dist, zone};

struct Weight{
    double dist;
    double zone;
};

struct Edge {
    int dest;
    std::list<std::string> lines;
    Weight weight;
};

struct Node {
    list<Edge> adj;
    double distance;
    bool visited;
    //TODO
    //Overkill?
    std::string stop;
    int parent;
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
    void dijkstra(int src, typeWeight type);
    list<string> shortPathDijkstra(int src, int dest, typeWeight type);
};

#endif
