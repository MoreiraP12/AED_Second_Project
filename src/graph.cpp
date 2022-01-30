#include "graph.h"
#include "minHeap.h"
#include "Exceptions.h"
#include "ShowStop.h"
#include <cmath>
#include <stack>
#include<algorithm>
#include <iomanip>

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

void Graph::addEdge(int src, int dest, std::string line, Weight weight, bool onFoot) {
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
    e.onFoot = onFoot;
    nodes[src].adj.push_back(e);
}


void Graph::createWalkingEdges(double maxDist){
    for(int j = 1; j <= n; j++){
        Stop from = nodes[j].stop;
        for(int i = 1; i <= n; i++) {
            if (i != j) { Stop to = nodes[i].stop;
                double dist = from.getDistance(to);
                if (dist < maxDist){
                    Weight w;
                    w.dist = dist;
                    if(from.getZone() != to.getZone()){
                        w.zone = 1;
                    }
                    else (w.zone = 0);
                    addEdge(n,i,"Walk",w);
                }
            }
        }
    }
}

void Graph::destroyWalkingEdges(){
    for(int i =1 ; i <= n; i++){
        vector<Edge>::iterator ptr;
        for (ptr = nodes[i].adj.begin(); ptr < nodes[i].adj.end(); ptr++){
            if(ptr->onFoot){
                nodes[i].adj.erase(ptr);
            }
        }
    }

}

void Graph::bfs(int v) {
    for (int v=1; v<=n; v++){
        nodes[v].visited = false;
        nodes[v].distance = -1;
        nodes[v].parent = -1;
    }
    queue<int> q;
    q.push(v);
    nodes[v].distance = 0;
    nodes[v]. visited = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].distance = nodes[u].distance + 1;
                nodes[w].parent = u;
            }
        }
    }
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
        Node n = nodes[u];
        for (auto e : nodes[u].adj) {
            int v = e.dest;
            double w = 0;
            if(u != src) {
                set<std::string> linesParent;
                if(nodes[u].parent != -1)
                    linesParent = getLines(nodes[u].parent, u);
                set<std::string> linesThis = getLines(u, v);
                set<std::string> intersect;
                std::set_intersection(linesParent.begin(), linesParent.end(), linesThis.begin(), linesThis.end(),
                                      std::inserter(intersect, intersect.begin()));
                if(intersect.empty()) w = 1;
                }
            if (!nodes[v].visited && nodes[u].distance + w < nodes[v].distance) {
                nodes[v].distance = nodes[u].distance + w;
                q.decreaseKey(v, nodes[v].distance);
                nodes[v].parent = u;
            }
        }
    }
}
/*
stack<Stop> Graph::shortPath(int src, int dest, typeWeight type){
    if(type == LINE) dijkstraLines(src);
    else if(type == STOPS) bfs(src);
    else dijkstra(src, type);

    stack<Stop> path;
    if(nodes[dest].distance == INF) throw NoPathAvailable();
    path.push(nodes[dest].stop);
    int v = dest;
    while (v != src){
        if(v == -1)
            throw NoPathAvailable();
        v = nodes[v].parent;
        path.push(nodes[v].stop);
    }
    return path;
}*/

stack<ShowStop> Graph::shortPath(int src, int dest, typeWeight type){
    if(type == LINE) dijkstraLines(src);
    else if(type == STOPS) bfs(src);
    else dijkstra(src, type);

    stack<ShowStop> path;
    if(nodes[dest].distance == INF) throw NoPathAvailable();
    path.push({nodes[dest].stop,{""}});
    int v = dest;
    while (v != src){
        if(v == -1)
            throw NoPathAvailable();
        std::set<string> lines;
        try{
            lines = getLines(nodes[v].parent, v);
        }catch(NoPathAvailable& e){
            e.printError();
        }
        v = nodes[v].parent;//TODO
        path.push({nodes[v].stop, lines});
    }
    return path;
}

set<string> Graph::getLines(int src, int dest){
    for(auto edge: nodes[src].adj){
        if(edge.dest == dest)
            return edge.lines;
    }
    throw NoPathAvailable();
}