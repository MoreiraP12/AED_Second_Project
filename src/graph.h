#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <stack>
#include<algorithm>
#include <set>
#include "stop.h"
#include "minHeap.h"
#include "showStop.h"
#include "exceptions.h"

#define INF (INT_MAX)

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
    /**
     * Constructor for the Graph. Initializes the vector of nodes with a
     * singleton once marking the position 0
     */
    Graph();

    /**
     * Creates and adds a Node to the graph. The Node encapsulates Stop s
     * @param s the Stop
     */
    void addNode(const Stop& s);

    /**
     * Creates and add an edge between nodes src and dest. Receives the line
     * which the edge represents. If there's already an edge between those two
     * stops, adds the new line to the list of lines. Receives the weight of
     * the edge as parameter, and a boolean with marks edges that don't represent
     * bus lines, but walking distances
     * @param src source node
     * @param dest destination node
     * @param line the line that connects the nodes
     * @param weight the weight of the edge
     * @param onFoot true if the edge is an walking edge
     */
    void addEdge(int src, int dest, const std::string& line, Weight weight, bool onFoot = false);

    /**
     * Creates edges that represent walking distances between stops. These
     * distances must be below the value specified in the parameter
     * @param maxDist the maximum walking distance
     */
    void createWalkingEdges(double maxDist);

    /**
     * Clears walking edges from the graph
     */
    void destroyWalkingEdges();

    /**
     * Retrieves the Stop object stored in the graph's node that's in the
     * position i of the nodes vector
     * @param i the index of the Node
     * @return the Stop stored in said Node
     */
    Stop elementAt(int i){
        return nodes[i].stop;
    }

    /**
     * Returns the size of the graph
     * @return the size of the graph
     */
    int size(){
        return nodes.size();
    }

    /**
     * Retrieves the lines between two Nodes
     * @param src the source Node
     * @param dest the destination Node
     * @return the lines of the edge that connects them
     */
    set<string> getLines(int src, int dest);

    /**
     *Runs BFS's algorithm to compute the minimum amount of nodes
     * visited to get to a certain node
     * specified through a parameter
     * Complexity O(|E|+|V|)
     * @param src the source node
     * @param dest destination node
     */
    void bfs(int v);

    /**
     * Runs Dijkstra's algorithm to compute the distance between src and
     * each node of the graph. The distance's value depends on the type
     * specified through the parameter
     * Complexity O(|E|+|V|log|V|)
     * @param src the source node
     * @param type the distance's specification parameter
     */
    void dijkstra(int src, typeWeight type);

    /**
     * Runs Dijktra's algorithm to compute the distance between src and
     * each node of the graph, considering 'line changes' as the parameter
     * that defines the distance between two nodes
     * @param src the source node
     */
    void dijkstraLines(int src);

    /**
     * Retrieves the shortest path between two nodes according to parameter
     * specification
     * @param src the source node
     * @param dest the destination node
     * @param type the specification
     * @return the shortest path between src and dest
     */
    stack<ShowStop> shortPath(int src, int dest, typeWeight type);
};

#endif
