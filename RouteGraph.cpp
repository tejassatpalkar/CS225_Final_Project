#include "RouteGraph.h"
#include "readFromFile.hpp"

#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::vector;

RouteGraph::RouteGraph(string fileName) {
    /* creates the graph */
    parseRoutes(fileName);
}

vector<RouteDistance> RouteGraph::getAllRoutes() {
    /* intiialize vector */
    vector<RouteDistance> routes;

    /* iterate through vertices */
    for (const Vertex& vertex : graph_.getVertices()) {
        /* check for next connected component and call BFS */
        if (!visitedMap_[vertex]) {
            BFS(vertex, routes);
        }
    }

    /* return routes */
    return routes; 
}


void RouteGraph::BFS(Vertex vertex, vector<RouteDistance>& routes) {
    /* declare queue */
    queue<Vertex> vertexStorage;

    /* initialize beginning values for BFS*/
    vertexStorage.push(vertex);
    visitedMap_[vertex] = true;

    /* continue while there's still vertices to traverse in this component */
    while (!vertexStorage.empty()) {
        /* get next vertex */
        Vertex currVertex = vertexStorage.front();
        vertexStorage.pop();

        /* iterate through adjacent vertices */
        for (const Vertex& adjVertex : graph_.getAdjacent(currVertex)) {
            /* check if not visited */
            if (!visitedMap_[adjVertex]) {
                /* update edge and visited state */
                graph_.setEdgeLabel(currVertex, adjVertex, "DISCOVERY");
                visitedMap_[adjVertex] = true;

                /* add to queue */
                vertexStorage.push(adjVertex);

                /* add to route */
            } 
            /* check for and update cross edges */
            else if (graph_.getEdgeLabel(currVertex, adjVertex) == "UNEXPLORED") {
                graph_.setEdgeLabel(currVertex, adjVertex, "CROSS");
            }
        }
    }
}


void RouteGraph::parseRoutes(string fileName) {
    /* creates a vector of strings */
    vector<string> data = file_to_vector(fileName);

    /* iterates through each entry */
    for (const string& entry : data) {

        /* creates a route object for parsing */
        Route route = parseEntry(entry);

        /* gets the source and destination */
        string source = route.first;
        string dest = route.second;

        /* edge case check for validity */
        if (source == "" || dest == "") {
            continue;
        }
        
        /* adds the vertices to the graph and map if nonexistant in the graph */
        if (!graph_.vertexExists(source)) {
            graph_.insertVertex(source);
            visitedMap_[source] = false;
        }
        if (!graph_.vertexExists(dest)) {
            graph_.insertVertex(dest);
            visitedMap_[dest] = false;
        }

        /* inserts the edge and sets the weight */
        graph_.insertEdge(source, dest);
        //graph_.setEdgeWeight(source, dest, route.getDistance());
        graph_.setEdgeLabel(source, dest, "UNEXPLORED");
    }


}

Route RouteGraph::parseEntry(string entry) {

    /* declare needed variables */
    string delimiter = ",";
    size_t pos = 0;
    std::string token;
    vector<string> vals;

    /* split by "," and add to vector 
       from: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c */
    while ((pos = entry.find(delimiter)) != std::string::npos) {
        token = entry.substr(0, pos);
        vals.push_back(token);
        entry.erase(0, pos + delimiter.length());
    }
    vals.push_back(entry);

    /* return an invalid route if the entry is invalid */
    if (vals.size() <= 4) {
        return Route("", "");
    }

    /* return the correct route otherwise */
    return Route(vals[2], vals[4]);
}