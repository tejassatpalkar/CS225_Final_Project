#pragma once

#include <string>

#include "readFromFile.hpp"
#include "graph.h"

using std::string;

class RouteGraph {


    public:

        /**
         * Default constructor that create the RouteGraph
         * @param fileName : the name of the file containing the routes
         */
        RouteGraph(string fileName);




    private:
    
        /**
         * Helper function to parse the data
         * Initializes the graph by creating a parsed Route object
         * @param fileName : the name of the file containing the routes
         */
        void parseRoutes(string fileName);

        Graph graph_ = Graph(true);

};