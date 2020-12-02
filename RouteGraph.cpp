#include "RouteGraph.h"
#include "Route.h"

#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::vector;

RouteGraph::RouteGraph(string fileName) {
    parseRoutes(fileName);
}


void RouteGraph::parseRoutes(string fileName) {
    /* creates a vector of strings */
    vector<string> data = file_to_vector(fileName);

    int num_valid = 0;

    /* iterates through each entry */
    for (const string& entry : data) {
        /* creates a route object for parsing */
        Route route(entry);

        /* edge case check for validity */
        if (!route.isValid()) {
            continue;
        }

        num_valid++;
        
        /* gets the source and destination */
        string source = route.getSource();
        string dest = route.getDest();

        /* adds the vertices if nonexistant */
        if (!graph_.vertexExists(source)) {
            graph_.insertVertex(source);
        }
        if (!graph_.vertexExists(dest)) {
            graph_.insertVertex(dest);
        }

        /* inserts the edge and sets the weight */
        graph_.insertEdge(source, dest);
        graph_.setEdgeWeight(source, dest, route.getDistance());
    }
    //graph_.print();

}