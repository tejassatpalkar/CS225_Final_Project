# pragma once

# include <utility>

using std::pair;

class Util{
    public:
        /**
         * This is a utility function that transfers the latitude and longitude of
         * the airport to a pixel in the output graph.
         */
        pair<int,int> location2graph(pair<float,float> location, int width, int height);
};