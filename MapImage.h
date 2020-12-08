#pragma once

#include "RouteGraph.h"
#include "AirportList.hpp"
#include "cs225/PNG.h"

#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;

typedef std::pair<int, int> Coordinate;

class MapImage {

    public:

        /**
        * Creates a map image by initializing a RouteGraph object
        * @param airportFile : the file location of the airport dataset
        * @param routeFile : the file location of the routes dataset
        */
        MapImage(string airportFile, string routeFile);

        /**
        * Draws the location and connection of airports on the image
        * @param outLocation : the desired image output
        */
        void drawAirports(string outLocation);


    private:

        /* data structure storing airport connections */
        RouteGraph graph_;

        /* map background image */
        cs225::PNG backgroundImage_;

        /* unordered map to lookup coordinates */
        unordered_map<string, Coordinate> locationMap_ = unordered_map<string, Coordinate>();

        /* image adjustments */
        int adjHeight_;
        int adjWidth_;
        int offset_;

        /**
        * Helper function to draw the border of every point on the map
        * @param coord : the coordinate of the location
        * @param color : the color of the border
        * @param png : the image to modify
        */
        void drawPointBorders(Coordinate coord, const cs225::HSLAPixel color, cs225::PNG& png);

        /**
        * Initializes the map to locate airport xy-coordinates for O(1) lookup
        * @param routes : a vector of RouteDistances obtained from the RouteGraph BFS
        */
        void initializeLocationMap(vector<RouteDistance> routes);

        /**
        * Helper function to add an airport to the unordered map
        * First checks to make sure the airport is not already in the unordered map
        * @param airport : the unique ID of the airport
        * @param location : the latitude/longitude location of the airport
        */
        void addLocation(string airport, Location location);
};