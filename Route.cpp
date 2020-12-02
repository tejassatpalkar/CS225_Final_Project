#include "Route.h"


Route::Route(string entry) {

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

    if (vals.size() <= 4) {
        isValid_ = false;
        return;
    }

    setVariables(vals[2], vals[4]);
}


void Route::setVariables(string sourceAirport, string destAirport) {
    //@TODO: change type from string to airport
    sourceAirport_ = sourceAirport;
    destAirport_ = destAirport;

    //@TODO: Calculate distances
    //distance_ = calculateDistance(sourceAirport_, destAirport_);
}

string Route::getSource() { return sourceAirport_; }

string Route::getDest() { return destAirport_; }

double Route::getDistance() { return distance_; }

bool Route::isValid() { return isValid_; }