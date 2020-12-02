#pragma once

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Route {

    public:
        /**
         * Parses data from a single row entry from the .dat file
         * @param entry : the string entry
         */
        Route(string entry);

        /* getters */
        string getSource();
        string getDest();
        double getDistance();
        bool isValid();
        

    private:
        //@TODO: change type to Airport w/ dict
        string sourceAirport_;
        string destAirport_;
        double distance_;
        bool isValid_ = true;

        /**
         * Sets the variables appropriately with given values
         * @param sourceAirport : the starting airport
         * @param destAirport : the ending airport
         */
        void setVariables(string sourceAirport, string destAirport);
};