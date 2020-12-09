#include "MapImage.h"
#include "cs225/PNG.h"
#include "Utility.h"
#include "math.h"

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
    /* store image to private variable */
    backgroundImageAirports_ = outImage;
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


void MapImage::drawRoute(string source, string dest){
    
    /* Creates Pixel to Color Routes */
    const cs225::HSLAPixel ROUTE_PIXEL = cs225::HSLAPixel(120, 1, 0.5, 1);
    cs225::PNG outImage(backgroundImageAirports_);

    /* Looks up prevously stored pixel coordinates of source and dest airports */

    /* TODO: Fix the lookup system */
    Coordinate start,end;
    // auto it = locationMap_.find(source);
    // if (it != locationMap_.end()){
    //      start= (*it).second;
    // }
    // else {return;}
    // it = locationMap_.find(dest);
    // if (it != locationMap_.end()){
    //      end= (*it).second;
    // }
    // else {return;}

    //Testing without looking up the coordinates
    start.first = outImage.width()/4;
    start.second = 100;
    end.first = outImage.width() - outImage.width()/3; 
    end.second = outImage.height() -300;

    /* Draws the Line between the two points */
    drawLine(start, end, ROUTE_PIXEL, outImage);
    outImage.writeToFile("outLine.png");

}

void MapImage::drawLine(Coordinate start, Coordinate end, const cs225::HSLAPixel color, cs225::PNG& png){

    // optional Make a small circle around the start and end points if time

    /* Implementation of the DDA algorithm with help from https://www.youtube.com/watch?v=W5P8GlaEOSI */
    double x1,x2, y1,y2, delta_x, delta_y, s, xinc, yinc;
    x1 = start.first;
    y1 = start.second;
    x2 = end.first;
    y2 = end.second;
    delta_x = x2-x1;
    delta_y = y2-y1;

    
    double stdDistance = sqrt(delta_x * delta_x + delta_y * delta_y);
    double wx1 = x1, wx2 = x2, wdelta_x;
    if (x1 <= x2){
        wx2 = wx2 - png.width();
    } else {
        wx1 = wx1 - png.width();
    }
    wdelta_x = wx2 - wx1;
    double wDistance = sqrt(wdelta_x * wdelta_x + delta_y * delta_y);

    if (wDistance <= stdDistance){
        delta_x = wdelta_x;
        x1 = wx1;
        x2 = wx2;
    }
    
    
    /* Essentailly checking if slope is greater than or less than one to determine step size */
    if (abs(delta_x) > abs(delta_y)){
        s = abs(delta_x);
    } else {
        s = abs(delta_y);
    }

    /*Compute the respective dimension increments */
    xinc = delta_x/s;
    yinc = delta_y/s;

    /* Replace pixel with color to mark path */
    for (unsigned i = 0; i < s; i++){
        int width = png.width();
        int x =  ((((int) round(x1)) % width) + width) % width;
        unsigned y = (unsigned)(round(y1));
        cs225::HSLAPixel & pixel = png.getPixel((unsigned) x, (unsigned)(round(y1)));
        
        pixel = color;
        x1 = x1 + xinc;
        y1 = y1 + yinc;
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