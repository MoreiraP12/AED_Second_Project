// AED 2021/2022 - Aula Pratica 09
// Pedro Ribeiro (DCC/FCUP) [03/01/2022]

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include "stop.h"

using namespace std;

class Graph {
    enum State{
        WHITE, GRAY, BLACK
    };
    struct Edge {
        int dest;   // Destination node
        std::pair<bool, double> weight; // An integer weight
        std::list<std::string> lines;
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        State color;
        int distance;
        bool visited;   // As the node been visited on a search?
        std::string stop;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph();

    void addNode(std::string s);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, std::pair<bool, double> weight);

    string elementAt(int i){
        return nodes[i].stop;
    }

    int size(){
        return nodes.size();
    }

    void printLines(int i) {
        for (auto edge : nodes[i].adj) {
            for (auto line : edge.lines)
                std::cout << line << " ";
            std::cout << endl;
        }
        std::cout << endl;
    }

    void printEdges(int i){
        for(auto edge : nodes[i].adj)
            std::cout << nodes[edge.dest].stop << " ";
        std::cout << endl;
    }


    // Depth-First Search: example implementation
    int dfs(int v);

    void dfsTopo(int v, list<int>&);
    bool cycleDfs(int v);
    // Breadth-First Search: example implementation
    void bfs(int v);
    void bfsDist(int v);

    // ----- Functions to implement in this class -----
    int outDegree(int v);
    int connectedComponents();
    int giantComponent();
    list<int> topologicalSorting();
    int distance(int a, int b);
    int diameter();
    bool hasCycle();
};

#endif
