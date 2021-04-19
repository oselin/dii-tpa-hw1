#include <iostream>
#include <string>
#include "car_trailer.h"

#include <fstream>
#include <streambuf>
#include <sstream>
using namespace std;

int main() {

    OselinDevice *device, dev;

    device = &dev;
    float width, height, radius;

    cout << "SVG width: ";
    //cin >>  width;
    width = 800;
    cout << "SVG height: ";
    //cin >> height;
    height = 600;
    cout << "Trailer's length: ";
    //cin >> device->length;
    device->length = 600;
    cout << "Trailer's height: ";
    //cin >> device->height;
    device->height = 270;

    radius = 40;
    //CONSTRAINS:
    oselin_init(device,width, height);
    oselin_trigonometry(device, width, height, radius);
    ofstream MyFile("test.svg");
    MyFile << oselin_to_svg(device,width,height);
    MyFile.close();
    return 0;
}
