# include "dijkstra.hpp"
# include "Utility.h"
# include <algorithm>
# include <list>
# include <iostream>

using std::pair;
using std::string;
using std::vector;
using std::remove;

Dijkstra::Dijkstra(RouteGraph obj){
    // Initialize the edges and graph
    Edge_ = obj.getAllRoutes();
    graph_ = obj.getGraph();
    // Genrate the map for routes and their indicated distance
    for (auto i : Edge_){
        Route_.insert(pair<Route,double>(i.first,distance(i.second.first,i.second.first)));
    }
    // Generate the map of nodes storing the information for each vertices when running Dijkstra's algorithm
    for (auto i : graph_.getVertices()){
        Vertex_.insert(pair<string,node>(i,node()));
    }
}

vector<string> Dijkstra::findShortestPath(string start, string end){
    Vertex_[start].dist = 0.0;
    vector<string> Q;
    string u;
    double alt;
    // Push the starting point
    Q.push_back(start);
    while(!Q.empty()){
        // find the smallest distance, set as visited and pop from Q
        u = find_min(Q);
        Vertex_[u].visited = true;
        Q.erase(remove(Q.begin(),Q.end(),u),Q.end());
        // end the algorithm if the end point is popped
        if (u == end) break;
        // update Q by pushing all unvisited neighbor nodes into Q
        for (auto v : graph_.getAdjacent(u)){
            if (Vertex_[v].visited) continue;
            Q.push_back(v);
            // update the state of the nodes
            alt = Vertex_[u].dist + Route_[pair<string,string>(u,v)];
            if (alt < Vertex_[v].dist){
                Vertex_[v].dist = alt;
                Vertex_[v].prev = u;
            }
        }
    }

    std::list<string> path;
    
    // back track to find the entire path
    u = end;
    if (Vertex_[u].prev != "UNDEFINED" || u ==start){
        while(u != "UNDEFINED"){
            path.push_front(u);
            u = Vertex_[u].prev;
        }
    }
    // transfer the path from vector to list
    vector<string> result(path.begin(),path.end());
    return result;
}

string Dijkstra::find_min(vector<string> Q){
    string min_node;
    double min = std::numeric_limits<float>::infinity();
    // traverse through the vector and returns the smallest distance
    for (auto i : Q){
        if (Vertex_[i].dist < min){
            min = Vertex_[i].dist;
            min_node = i;
        }
    }
    return min_node;
}

Dijkstra::node::node(){
    // initialize the values of node
    visited = false;
    prev = "UNDEFINED"; 
    dist = std::numeric_limits<float>::infinity();
}