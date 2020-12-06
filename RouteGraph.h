#pragma once

#include <string>
#include <unordered_map>
#include <queue>
#include "graph.h"

using std::string;
using std::unordered_map;
using std::queue;
using std::pair;

typedef pair<string, string> Route;

typedef pair<Route, double> RouteDistance; 

class RouteGraph {

    public:

        /**
         * Default constructor that create the RouteGraph
         * @param fileName : the name of the file containing the routes
         */
        RouteGraph(string fileName);

        /**
         * Finds all of the routes in the data
         * @return a vector of objects representing a route
         */
        vector<RouteDistance> getAllRoutes();

        /* getters */

        int getNumAirports();

        int getNumConnections();

        Graph getGraph();

    private:
    
        /**
         * Helper function to parse the data
         * Initializes the graph by creating a parsed Route object
         * @param fileName : the name of the file containing the routes
         */
        void parseRoutes(string fileName);

        /**
         * Parses single entry of the data table
         * @param entry : a single entry of the data table
         * @return object representing the route
         */
        Route parseEntry(string entry);

        /**
         * Helper BFS function that uses a given vertex
         * @param vertex : The current vertex
         * @param routes : A list of routes
         */
        void BFS(Vertex vertex, vector<RouteDistance>& routes);

        /* initialize graph object */
        Graph graph_ = Graph(true, true);

        /* initialize map for tracking visits */
        unordered_map<string, bool> visitedMap_ = unordered_map<string, bool>();
};