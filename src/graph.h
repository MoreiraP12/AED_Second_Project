#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <stack>
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
    Stop stop;
    int parent;
};

class Graph {
    int n;
    vector<Node> nodes;

public:
    Graph();
    void addNode(Stop s);
    void addEdge(int src, int dest, std::string line, Weight weight);
    Stop elementAt(int i){
        return nodes[i].stop;
    }
    int size(){
        return nodes.size();
    }
    void dijkstra(int src, typeWeight type);
    stack<Stop> shortPathDijkstra(int src, int dest, typeWeight type);
};

#endif
