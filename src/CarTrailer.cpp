
#include "car_trailer.h"
#include <iostream>
#include <string>
using namespace std;/*
 *  Source for the not-part-of-a-library class Fraction
 *
 */


string svg;

void oselin_trigonometry(){}

string oselin_stringwheels(Oselin_Wheel rear, Oselin_Wheel front){}

string oselin_stringfloors(Oselin_Floor down, Oselin_Floor up){}

string oselin_stringaxis(Oselin_Axis rear, Oselin_Axis front){}

string oselin_stringjoints(Oselin_Joint back, Oselin_Joint forward){}

int oselin_init(int a){
    return a;
}

string oselin_to_svg(OselinDevice device){

    string svg;

    svg = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n<svg xmlns='http://www.w3.org/2000/svg' width="
    
    + to_string(device.width) + "' height='"

    + to_string(device.height) + "'>";

    return svg;
}
