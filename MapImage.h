#pragma once

#include "RouteGraph.h"
#include "AirportList.hpp"
#include "cs225/PNG.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

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

        /**
        * Helper function to draw the border of every point on the map
        * @param coord : the coordinate of the location
        * @param color : the color of the border
        * @param png : the image to modify
        */
        void drawPointBorders(Coordinate coord, const cs225::HSLAPixel color, cs225::PNG& png);
};