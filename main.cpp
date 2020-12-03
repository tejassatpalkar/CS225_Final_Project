#include "Utility.h"
#include <iostream>


int main() {

    std::pair<double,double> c2(1, 1);
    std::pair<double,double> c1(1,1);
    Util u;
    
    std::cout <<  u.distance(c1,c2) << std::endl;
    std::cout << "expected: " << std::endl;
    return 0;
}