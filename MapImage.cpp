#include "MapImage.h"
#include "cs225/PNG.h"
#include "Utility.h"

MapImage::MapImage(string airportFile, string routeFile) {
    /* create the airport list */
	AirportList airportList(airportFile);

	/* initialize the route graph and pass in the airport list */
	graph_ = RouteGraph(routeFile, airportList);

    /* initialize the file to read from */
    backgroundImage_.readFromFile("images/map.png");

    /* initialze image adjustments */
    adjHeight_ = 2 * backgroundImage_.height();
    adjWidth_ = backgroundImage_.width();
    offset_ = 300;

    /* initialze the map for ease of access to coordinates */
    initializeLocationMap(graph_.getAllRoutes());
}


void MapImage::drawAirports(string outLocation) {
    /* create a copy of the image to draw the airports */
    cs225::PNG outImage(backgroundImage_);

    /* creates the center and border pixels */
    const cs225::HSLAPixel POINT_PIXEL = cs225::HSLAPixel(20, 1, 0.5, 1);
    const cs225::HSLAPixel BORDER_PIXEL = cs225::HSLAPixel(20, 1, 0.65, 1);

    /* iterate through every item in the unordered map */
    for (auto locationItr = locationMap_.begin(); locationItr != locationMap_.end(); ++locationItr) {

        /* get the coordinate value */
        Coordinate coord = locationItr->second;

        /* draw on the picture accordingly */
        outImage.getPixel(coord.first, coord.second) = POINT_PIXEL;
        drawPointBorders(coord, BORDER_PIXEL, outImage);
    }

    /* output the image file */
    outImage.writeToFile(outLocation);
}

void MapImage::drawPointBorders(Coordinate coord, const cs225::HSLAPixel color, cs225::PNG& png) {

    /* check lower bounds */
    if (coord.first > 0) {
        png.getPixel(coord.first - 1, coord.second) = color;
    }
    if (coord.second > 0) {
        png.getPixel(coord.first, coord.second - 1) = color;
    }

    /* check upper bounds */
    if (coord.first < (int) png.width() - 1) {
        png.getPixel(coord.first + 1, coord.second) = color;
    }
    if (coord.second < (int) png.height() - 1) {
        png.getPixel(coord.first, coord.second + 1) = color;
    }
}

void MapImage::initializeLocationMap(vector<RouteDistance> routes) {

    /* iterate through each route */
    for (const RouteDistance& routeDistance : routes) {
        /* grab our needed variables */
        Route route = routeDistance.first;
        pair<Location, Location> locations = routeDistance.second;

        /* try to add both to the unordered map */
        addLocation(route.first, locations.first);
        addLocation(route.second, locations.second);
    }
}

void MapImage::addLocation(string airport, Location location) {
    /* edge case if already in the map */
    if (locationMap_.find(airport) != locationMap_.end()) {
        return;
    }

    /* otherwise, add the coordinate to the map */
    locationMap_[airport] = location2graph(location, adjWidth_, adjHeight_, offset_);
}