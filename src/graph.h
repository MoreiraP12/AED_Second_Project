#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <stack>
#include "Stop.h"
#include "ShowStop.h"
#include <set>
#define INF (INT_MAX/2)

using namespace std;

enum typeWeight{DIST, ZONE, LINE, STOPS};

struct Weight{
    double dist;
    double zone;
};

struct Edge {
    int dest;
    bool onFoot;
    set<std::string> lines;
    Weight weight;
};

struct Node {
    vector<Edge> adj;
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
    void addEdge(int src, int dest, std::string line, Weight weight, bool onFoot = false);
    void createWalkingEdges(double maxDist);
    void destroyWalkingEdges();

    Stop elementAt(int i){
        return nodes[i].stop;
    }
    int size(){
        return nodes.size();
    }

    set<string> getLines(int src, int dest);
    void bfs(int v);
    void dijkstra(int src, typeWeight type);
    void dijkstraLines(int src);
    stack<ShowStop> shortPath(int src, int dest, typeWeight type);
};

#endif
