# pragma once

# include <vector>
# include <string>
# include <map>
# include "AirportList.hpp"
# include "RouteGraph.h"
# include "Utility.h"
# include <limits>
# include "graph.h" 

using std::vector;
using std::string;
using std::map;

typedef pair<string, string> Route;
typedef pair<float, float> Location;
typedef pair<Route, pair<Location, Location>> RouteDistance; 


class Dijkstra {
    public:
        /**
         * A class that keeps record of whether the node has been visited
         * and its distance and previous nodes
         */
        class node{
            public:
                node();
                bool visited;
                string prev;
                double dist;
        };

        /**
         * Constructor that initializes all the private variables in the class
         * and generates maps that are handy for Dijkstra's algorithm
         */
        Dijkstra(RouteGraph obj);

        /**
         * The search function that applies Dijkstra's algorithm to find
         * the shortest path for the provided start and end nodes
         */
        vector<string> findShortestPath(string start, string end);

    private:
        /**
         * The map that maps each airport vertex with a node class to record status
         * to facilitate the Dijkstra's algorithm
         */
        map<string,node> Vertex_;

        // A vector thoring all the routes and the location of starting and ending points
        vector<RouteDistance> Edge_;

        // Updated from Edge_ and change the location pair into a distance
        map<Route,double> Route_;

        // helper function that find the minimum distance node in the vector
        string find_min(vector<string> Q);

        // graph structure that stores the generated directed graph
        Graph graph_ = Graph(true,true);
};