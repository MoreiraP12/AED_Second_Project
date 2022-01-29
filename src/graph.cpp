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

bool Graph::bfs(int src, int dest, int v, int pred[], int dist[]){
    // a queue to maintain queue of vertices whose
    // adjacency list is to be scanned as per normal
    // DFS algorithm
    list<int> queue;

    // boolean array visited[] which stores the
    // information whether ith vertex is reached
    // at least once in the Breadth first search
    bool visited[v];

    // initially all vertices are unvisited
    // so v[i] for all i is false
    // and as no path is yet constructed
    // dist[i] for all i set to infinity
    for (int i = 0; i < v; i++) {
        visited[i] = false;
        dist[i] = INT_MAX;
        pred[i] = -1;
    }

    // now source is first to be visited and
    // distance from source to itself should be 0
    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);

    // standard BFS algorithm
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        for (std::vector<Edge>::const_iterator it = nodes[u].adj.begin(); it != nodes[u].adj.end(); ++it) {
            if (nodes[it->dest].visited == false) {
                nodes[it->dest].visited = true;
                dist[it->dest] = dist[u] + 1;
                pred[it->dest] = u;
                queue.push_back(it->dest);

                // We stop BFS when we find
                // destination.
                if (it->dest == dest)
                    return true;
            }
        }
    }

    return false;
}

// utility function to print the shortest distance
// between source vertex and destination vertex
void Graph::shortPathBFS(int s, int dest, int v){
    // predecessor[i] array stores predecessor of
    // i and distance array stores distance of i
    // from s
    int pred[v], dist[v];

    if (bfs(s, dest, v, pred, dist) == false) {
        cout << "Given source and destination"
             << " are not connected";
        return;
    }

    // vector path stores the shortest path
    vector<int> path;
    int crawl = dest;
    path.push_back(crawl);
    while (pred[crawl] != -1) {
        path.push_back(pred[crawl]);
        crawl = pred[crawl];
    }

    // distance from source is in distance array
    cout << "Shortest path length is : "
         << dist[dest];

    // printing path from source to destination
    cout << "\nPath is::\n";
    for (int i = path.size() - 1; i >= 0; i--)
        cout << path[i] << " ";
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
