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

    /**
     * CHOSEN PARAEMTERS:
     * @param SVG WIDTH
     * @param SVG HEIGHT
     * @param WHEEL'S RADIUS -> 16" 17" 18"
     * @param CAR-PER-TRAILER ->1 OR 2 PER TRAILER
     * @param HEIGHT -> 1 OR 2 FLOORS
     * @param CAR'S LENGTH -> TRAILER LENGTH = CAR-PER-TRAILER * CAR'S LENGTH
     * @param CAR'S HEIGHT -> TRAILER HEIGHT = CAR'S HEIGHT * HEIGHT
     * */

    float svgwidth, svgheight, radius, carlength, carheight;
    int ncars = 0, height = 1;
    
    
    //1-- 800
    cout << "SVG width: ";
    //cin >>  svgwidth;
    svgwidth = 800;
    
    //2-- 600
    cout << "SVG height: ";
    //cin >> svgheight;
    svgheight = 600;
    //3--
    cout << "CAR LENGTH: ";
    //cin >>  carlength;
    carlength = 200;
    //4--
    cout << "CAR HEIGHT: ";
    //cin >>  carheight;
    carheight = 100;
    //5--
    cout << "WHEEL RADIUS [16, 17, 18]: ";
    cin >>  radius;

    //6--
    cout << "Cars-per-trailer [1, 2]: ";
    cin >> ncars;

    //7--
    cout << "Number of floors [1, 2]: ";
    cin >> height;

    //CONSTRAINS:
    
    float margin = svgwidth/10;
    device->length = carlength * ncars + (ncars+1)*margin;
    device->height = carheight * height + 100;
    oselin_init(device, svgwidth, svgheight, radius, carlength, carheight, ncars, height, margin);
    oselin_trigonometry(device, svgwidth, svgheight, radius);

    //SAVING TO FILE
    ofstream MyFile("test.svg");
    MyFile << oselin_to_svg(device, svgwidth, svgheight, height);
    MyFile.close();

    return 0;
}
