# include "Utility.h"
# include <utility>
# include <cmath>

using std::pair;

pair<int,int> Util::location2graph(pair<float,float> location, int width, int height){
    int w,h;
    w = floor(width/2.0*(1+location.second/180.0)+0.5);
    h = floor(height/2.0*(1+location.first/180.0)+0.5);
    return pair<int,int>(w,h);
}