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
}


void MapImage::drawAirports(string outLocation) {
    /* create a copy of the image to draw the airports */
    cs225::PNG outImage(backgroundImage_);

    /* get the image height and width */
    const int HEIGHT = 2 * outImage.height();
    const int WIDTH = outImage.width();

    /* creates the center and border pixels */
    const cs225::HSLAPixel POINT_PIXEL = cs225::HSLAPixel(20, 1, 0.5, 1);
    const cs225::HSLAPixel BORDER_PIXEL = cs225::HSLAPixel(20, 1, 0.65, 1);

    /* get all of the routes using BFS */
    vector<RouteDistance> routes = graph_.getAllRoutes();

    for (const RouteDistance& routeDistance : routes) {
        /* grab our needed variables */
        Route route = routeDistance.first;
        pair<Location, Location> locations = routeDistance.second;

        /* get the two coordinates */
        Coordinate startCoord = location2graph(locations.first, WIDTH, HEIGHT, 300);
        Coordinate endCoord = location2graph(locations.second, WIDTH, HEIGHT, 300);

        /* replace the center pixels of the two coordinates */
        outImage.getPixel(startCoord.first, startCoord.second) = POINT_PIXEL;
        outImage.getPixel(endCoord.first, endCoord.second) = POINT_PIXEL;

        drawPointBorders(startCoord, BORDER_PIXEL, outImage);
        drawPointBorders(endCoord, BORDER_PIXEL, outImage);
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