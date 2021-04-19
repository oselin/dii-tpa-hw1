
#include "car_trailer.h"
#include <iostream>
#include <string>
#include <cmath>



using namespace std;/*
 *  Source for the not-part-of-a-library class Fraction
 *
 */


int oselin_init(OselinDevice *dev, float width, float height){
    if (dev->length > width || dev->height > height){
        
        cout << "OSELIN::INIT - ERROR CODE 1" << endl;
        return 1;
    }
    return 0;
}


void oselin_trigonometry(OselinDevice *dev, float width, float height, float r){

    //DOWNFLOOR
    dev->downfloor.x = (width-dev->length)/2;
    dev->downfloor.y = (height-2*DOWNOFFSET);
    dev->downfloor.width = dev->length;
    dev->downfloor.height = dev->downfloor.width/10;
    dev->downfloor.stroke = dev->downfloor.height/20;

    //UPFLOOR
    dev->upfloor.x = (width-dev->length)/2;
    dev->upfloor.y = (height-2*DOWNOFFSET)-dev->height;
    dev->upfloor.width = dev->length;
    dev->upfloor.height = dev->upfloor.width/10;
    dev->upfloor.stroke = dev->upfloor.height/20;

    //REAR WHEEL
    dev->rearwheel.x = dev->downfloor.x + WHEELOFFSET;
    dev->rearwheel.y = height-DOWNOFFSET;
    dev->rearwheel.radius = r;
    dev->rearwheel.stroke = r/10;
    
    
    //FRONT WHEEL
    dev->frontwheel.x = dev->downfloor.x + dev->length - WHEELOFFSET;
    dev->frontwheel.y = height-DOWNOFFSET;
    dev->frontwheel.radius = r;
    dev->frontwheel.stroke = r/10;


    //REAR JOINT
    dev->rearjoint.body.x = dev->downfloor.x - DOWNOFFSET;
    dev->rearjoint.body.y = dev->downfloor.y+DOWNOFFSET/2;
    dev->rearjoint.body.width = DOWNOFFSET;
    dev->rearjoint.body.height = DOWNOFFSET/5;
    dev->rearjoint.body.stroke = dev->rearjoint.body.height/20;
    dev->rearjoint.head.x = dev->rearjoint.body.x;
    dev->rearjoint.head.y = dev->rearjoint.body.y + dev->rearjoint.body.height/2;
    dev->rearjoint.head.radius = r/4;
    dev->rearjoint.head.stroke = r/10;
    dev->rearjoint.head.innercolor = "";
    dev->rearjoint.head.outercolor = "white";



    //FRONT JOINT
    dev->frontjoint.body.x = dev->downfloor.x + dev->length;
    dev->frontjoint.body.y = dev->downfloor.y+DOWNOFFSET/2;
    dev->frontjoint.body.width = DOWNOFFSET;
    dev->frontjoint.body.height = DOWNOFFSET/5;
    dev->frontjoint.body.stroke = dev->frontjoint.body.height/20;
    dev->frontjoint.head.x = dev->frontjoint.body.x + dev->frontjoint.body.width;
    dev->frontjoint.head.y = dev->frontjoint.body.y + dev->rearjoint.body.height/2;
    dev->frontjoint.head.radius = r/4;
    dev->frontjoint.head.stroke = r/10;
    dev->frontjoint.head.innercolor = "";
    dev->frontjoint.head.outercolor = "white";

    
    //REAR AXIS
    dev->rearaxis.body.x = dev->length/3 + dev->upfloor.x;
    dev->rearaxis.body.y = dev->upfloor.y;
    dev->rearaxis.body.height = dev->height + dev->downfloor.height;
    dev->rearaxis.body.width = dev->height/10;
    dev->rearaxis.body.stroke = dev->rearaxis.body.width/20;
    
    dev->rearaxis.topscrew.innercolor = "";
    dev->rearaxis.topscrew.outercolor = "white";
    dev->rearaxis.topscrew.radius = dev->rearaxis.body.width /3;
    dev->rearaxis.topscrew.stroke = r/10;
    dev->rearaxis.topscrew.x = dev->rearaxis.body.width/2 + dev->rearaxis.body.x;
    dev->rearaxis.topscrew.y = dev->rearaxis.body.width/2 + dev->rearaxis.body.y;
    
    
    dev->rearaxis.bottomscrew.innercolor = "";
    dev->rearaxis.bottomscrew.outercolor = "white";
    dev->rearaxis.bottomscrew.radius = dev->rearaxis.body.width /3;
    dev->rearaxis.bottomscrew.stroke = r/10;
    dev->rearaxis.bottomscrew.x = dev->rearaxis.body.width/2 + dev->rearaxis.body.x;
    dev->rearaxis.bottomscrew.y = -dev->rearaxis.body.width/2 + dev->rearaxis.body.y + dev->rearaxis.body.height;
    dev->rearaxis.rotationpoint[0] = dev->rearaxis.body.x + dev->rearaxis.body.width/2;
    dev->rearaxis.rotationpoint[1] = dev->rearaxis.body.y + dev->rearaxis.body.height/2;
        
    //dev->rearaxis.rotationpoint [0] = dev->rearaxis.body.x + dev->rearaxis.body.width/2;
    //dev->rearaxis.rotationpoint [1] = dev->rearaxis.body.y + dev->rearaxis.body.width/2;
    
    
    
    //FRONT AXIS
    dev->frontaxis.body.x = dev->length*2/3 + dev->upfloor.x;
    dev->frontaxis.body.y = dev->upfloor.y;
    dev->frontaxis.body.height = dev->height + dev->downfloor.height;
    dev->frontaxis.body.width = dev->height/10;
    dev->frontaxis.body.stroke = dev->frontaxis.body.width/20;
    
    dev->frontaxis.topscrew.innercolor = "";
    dev->frontaxis.topscrew.outercolor = "white";
    dev->frontaxis.topscrew.radius = dev->frontaxis.body.width /3;
    dev->frontaxis.topscrew.stroke = r/10;
    dev->frontaxis.topscrew.x = dev->frontaxis.body.width/2 + dev->frontaxis.body.x;
    dev->frontaxis.topscrew.y = dev->frontaxis.body.width/2 + dev->frontaxis.body.y;
 
    dev->frontaxis.bottomscrew.innercolor = "";
    dev->frontaxis.bottomscrew.outercolor = "white";
    dev->frontaxis.bottomscrew.radius = dev->frontaxis.body.width /3;
    dev->frontaxis.bottomscrew.stroke = r/10;
    dev->frontaxis.bottomscrew.x = dev->frontaxis.body.width/2 + dev->frontaxis.body.x;
    dev->frontaxis.bottomscrew.y = -dev->frontaxis.body.width/2 + dev->frontaxis.body.y + dev->frontaxis.body.height;
    dev->frontaxis.rotationpoint[0] = dev->frontaxis.body.x + dev->frontaxis.body.width/2;
    dev->frontaxis.rotationpoint[1] = dev->frontaxis.body.y + dev->frontaxis.body.height/2;
    
    //dev->frontaxis.rotationpoint [1] = dev->frontaxis.body.x + dev->frontaxis.body.width/2;
    //dev->frontaxis.rotationpoint [2] = dev->frontaxis.body.y + dev->frontaxis.body.width/2;
}


string oselin_wheeltoSVG(Oselin_Wheel wheel){
    string str;
    str += "\n<circle";
    str += " cx= '" + to_string(wheel.x) + "'";
    str += " cy= '" + to_string(wheel.y) + "'";
    str += " r= '" + to_string(wheel.radius) + "'";
    str += " stroke= '" + wheel.strokecolor + "'";
    str += " stroke-width= '" + to_string(wheel.stroke) + "'";
    str += " fill= '" + wheel.outercolor + "'";
    str += " />";

    if (wheel.innercolor != ""){
        str += "\n<circle";
        str += " cx= '" + to_string(wheel.x) + "'";
        str += " cy= '" + to_string(wheel.y) + "'";
        str += " r= '" + to_string(wheel.radius*3/4) + "'";
        str += " stroke= '" + wheel.strokecolor + "'";
        str += " stroke-width= '" + to_string(wheel.stroke) + "'";
        str += " fill= '" + wheel.innercolor + "'";
        str += " />";   
    }

   

    return str;
}


string oselin_floortoSVG(Oselin_Floor floor){
    string str = "\n<rect  ";
    str += "x='" + to_string(floor.x) + "'";
    str += " y='" + to_string(floor.y) + "'";
    str += " width='" + to_string(floor.width) + "'";
    str += " height='" + to_string(floor.height) + "'";
    str += " style='stroke-width: " + to_string(floor.stroke) + ";";
    str += " stroke:" + floor.strokecolor + "'";
    str += " fill= '" + floor.fillingcolor + "'";
    str += " />";
    return str;
}


string oselin_axistoSVG(Oselin_Axis steel){
    string str = "\n<g transform='rotate(";
    str += to_string(steel.angle) + "," + to_string(steel.rotationpoint[0]) + "," + to_string(steel.rotationpoint[1]);
    str += ")'>";
    str += oselin_floortoSVG(steel.body);
    
    str += oselin_wheeltoSVG(steel.bottomscrew) + oselin_wheeltoSVG(steel.topscrew);
    str += "\n</g>";
    return str;
}


string oselin_jointtoSVG(Oselin_Joint joint){
    string str;
    str = oselin_floortoSVG(joint.body) + oselin_wheeltoSVG(joint.head);
    return str;
}


string oselin_to_svg(OselinDevice *device, float width, float height){

    string svg;

    svg = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n<svg xmlns='http://www.w3.org/2000/svg' width= '"
    
    + to_string(width) + " '  height= '"

    + to_string(height) + "' >";


    svg += "\n" + oselin_jointtoSVG(device->rearjoint);

    svg += "\n" + oselin_jointtoSVG(device->frontjoint);

    svg += "\n" + oselin_floortoSVG(device->downfloor);

    svg += "\n" + oselin_floortoSVG(device->upfloor);

    svg += "\n" + oselin_wheeltoSVG(device->frontwheel);

    svg += "\n" + oselin_wheeltoSVG(device->rearwheel);

    svg += "\n" + oselin_axistoSVG(device->rearaxis);

    svg += "\n" + oselin_axistoSVG(device->frontaxis);


    svg += "\n</svg>";

    return svg;
}
