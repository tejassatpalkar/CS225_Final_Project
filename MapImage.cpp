#include "MapImage.h"
#include "cs225/PNG.h"
#include "Utility.h"

MapImage::MapImage(string airportFile, string routeFile) {
    /* create the airport list */
	AirportList airportList(airportFile);

	/* initialize the route graph and pass in the airport list */
	graph_ = RouteGraph(routeFile, airportList);

    /* initialize the file to read from */
    backgroundImage_.readFromFile("images/test.png");
}


void MapImage::drawAirports(string outLocation) {
    /* create a copy of the image to draw the airports */
    cs225::PNG outImage(backgroundImage_);

    /* get the image height and width */
    const int HEIGHT = 2 * outImage.height();
    const int WIDTH = outImage.width();

    /* create red pixel */
    const cs225::HSLAPixel RED = cs225::HSLAPixel(360, 100, 50);

    /* get all of the routes using BFS */
    vector<RouteDistance> routes = graph_.getAllRoutes();

    for (const RouteDistance& routeDistance : routes) {
        /* grab our needed variables */
        Route route = routeDistance.first;
        pair<Location, Location> locations = routeDistance.second;

        /* get the two coordinates */
        Coordinate startCoord = location2graph(locations.first, WIDTH, HEIGHT, 300);
        Coordinate endCoord = location2graph(locations.second, WIDTH, HEIGHT, 300);

        /* replace the pixels of the two coordinates */
        outImage.getPixel(startCoord.first, startCoord.second) = RED;
        outImage.getPixel(endCoord.first, endCoord.second) = RED;
    }

    /* output the image file */
    outImage.writeToFile(outLocation);
}