#include "graph.h"
#include "minHeap.h"
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
            //Eventually fix this
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

void Graph::dijkstra(int src, typeWeight type) {
    MinHeap<int, int> q(n, -1);
    for (int v=1; v<=n; v++) {
        nodes[v].distance = INF;
        q.insert(v, INF);
        nodes[v].visited = false;
    }
    nodes[src].distance = 0;
    q.decreaseKey(src, 0);
    nodes[src].parent = src;
    while (q.getSize()>0) {
        int u = q.removeMin();
        nodes[u].visited = true;
        for (auto e : nodes[u].adj) {
            int v = e.dest;
            double w;
            switch (type) {
                case dist:
                    w = e.weight.dist;
                    break;
                case zone:
                    w = e.weight.zone;
                    break;
            }
            if (!nodes[v].visited && nodes[u].distance + w < nodes[v].distance) {
                nodes[v].distance = nodes[u].distance + w;
                q.decreaseKey(v, nodes[v].distance);
                nodes[v].parent = u;
            }
        }
    }
}

list<string> Graph::shortPathDijkstra(int src, int dest, typeWeight type){
    dijkstra(src, type);
    list<string> path;
    if(nodes[dest].distance == INF) return path;
    path.push_back(nodes[dest].stop);
    int v = dest;
    while (v != dest){
        v = nodes[v].parent;
        path.push_back(nodes[v].stop);
    }

    return path;
}
