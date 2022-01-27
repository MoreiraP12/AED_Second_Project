#include "graph.h"
#include <cmath>
#include <stack>

Graph::Graph() {
    n = 1;
    Node n;
    nodes.push_back(n);
    hasDir = true;
}

void Graph::addNode(std::string s){
    n++;
    Node n;
    n.distance = 0;
    n.visited = false;
    n.stop = s;
    nodes.push_back(n);
}

void Graph::addEdge(int src, int dest, std::string line, Weight weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    for(auto edge : nodes[src].adj) {
        if (edge.dest == dest) {
            //Eventualy fix this
            edge.lines.push_back(line);
            return;
        }
    }
    Edge e;
    e.dest = dest;
    e.lines.push_back(line);
    e.weight = weight;
    nodes[src].adj.push_back(e);
}

