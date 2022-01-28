#include "graph.h"
#include "minHeap.h"
#include <cmath>
#include <stack>

Graph::Graph() {
    n = 1;
    Node n;
    nodes.push_back(n);
}

void Graph::addNode(Stop s){
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
            edge.lines.insert(line);
            return;
        }
    }
    Edge e;
    e.dest = dest;
    e.lines.insert(line);
    e.weight = weight;
    nodes[src].adj.push_back(e);
}

void Graph::dijkstra(int src, typeWeight type) {
    MinHeap<int, double> q(n-1, -1);
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
                case DIST:
                    w = e.weight.dist;
                    break;
                case ZONE:
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

void Graph::dijkstraLines(int src) {
    MinHeap<int, double> q(n-1, -1);
    for (int v=1; v<=n; v++) {
        nodes[v].distance = INF;
        q.insert(v, INF);
        nodes[v].parent = -1;
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
            set<std::string> lines;
            if(nodes[u].parent != -1){
                for (auto ed : nodes[nodes[u].parent].adj) {
                    if (ed.dest == u)
                        lines = ed.lines;
                }
                bool change = true;
                for (auto line : lines) {
                    if (e.lines.find(line) != lines.end()) {

                        change = false;
                        break;
                    }
                }
                //if not, w = 1
                if (change) w = 1;
            }
            if (!nodes[v].visited && nodes[u].distance + w < nodes[v].distance) {
                nodes[v].distance = nodes[u].distance + w;
                q.decreaseKey(v, nodes[v].distance);
                nodes[v].parent = u;
            }
        }
    }
}

stack<Stop> Graph::shortPathDijkstra(int src, int dest, typeWeight type){
    if(type == LINE) dijkstraLines(src);
    else dijkstra(src, type);
    stack<Stop> path;
    if(nodes[dest].distance == INF) return path;
    path.push(nodes[dest].stop);
    int v = dest;
    while (v != src){
        v = nodes[v].parent;
        path.push(nodes[v].stop);
    }
    return path;
}
