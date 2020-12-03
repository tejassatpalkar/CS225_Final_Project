#pragma once


#include<math.h>
#include <utility> 

/**
 * Utility Class for Calculations
 * 
 */
class Util{
    public:
    /**
     * Finds the distance in km between two coordinates on the map
     * @param coordinate1 Coordinate of First Airport (Latitude, Longitude) 
     * @param coordinate2 Coordinate of Second Airport (Latitude, Longitude)
     * @return The distance between the two coordinates ignoring elevation
     */
    double distance(std::pair<double , double> coordinate1, std::pair<double,double> coordinate2);
};


    




