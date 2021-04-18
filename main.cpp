#include <iostream>
#include <string>
#include "car_trailer.h"

#include <fstream>
#include <streambuf>
#include <sstream>
using namespace std;

int main() {

    Oselin_Wheel frontwheel;
    frontwheel.x = 630;
    frontwheel.y = 550;
    frontwheel.radius = 40;
    frontwheel.strokecolor = "black";
    frontwheel.innercolor = "gray";
    frontwheel.outercolor = "black";
    frontwheel.stroke = 3;

    cout << "2testout" << endl;

    OselinDevice dev;
    ofstream MyFile("test.svg");
    MyFile << oselin_to_svg(dev);
    MyFile.close();
    return 0;
}
