
#include "car_trailer.h"
#include <iostream>
#include <string>
#include <cmath>



using namespace std;/*
 *  Source for the not-part-of-a-library class Fraction
 *
 */


int oselin_init(OselinDevice *dev, float svgwidth, float svgheight, float radius, float carlength, float carheight, int ncar, int height, float margin){
    
    if (svgwidth < dev->length){
        cout << "INIT:: WIDTH ERROR" << endl;
    }
    if (ncar ==1 && height == 2){
        cout << "INIT:: STRUCTURAL ERROR" << endl;
    }
    return 0;
}

void trigfloors(OselinDevice *dev, float width, float height, string m){

    Oselin_Floor *f; int mode;
    if (m == "down") {
        mode = 0;
        f= &dev->downfloor;
    }
    else {
        mode = 1;
        f = &dev->upfloor;
    }

    f->x = (width-dev->length)/2;
    f->y = (height-2*DOWNOFFSET) - mode*dev->height;
    f->width = dev->length;
    f->height = height/10;
    f->stroke = f->height/20;

}

void trigwheel(OselinDevice *dev, float height, float radius, string m){
    int mode;
    Oselin_Wheel *wheel;
    if (m=="rear") {
        mode = 0;
        wheel = &dev->rearwheel;
        }
    else {
        mode = 1;
        wheel = &dev->frontwheel;
        }
    float wheeloffset = dev->length/12;
    //REAR WHEEL
    wheel->x = dev->downfloor.x + pow(-1,mode)* wheeloffset + mode*dev->length;
    wheel->y = height-DOWNOFFSET;
    wheel->radius = radius;
    wheel->stroke = radius/10;
}

void trigjoint(OselinDevice *dev, float radius,string m){

    Oselin_Joint *joint; int mode;
    if (m =="rear"){
        mode = 0;
        joint = &dev->rearjoint;
    }
    else{
        mode = 1;
        joint = &dev->frontjoint;
    }
    
    joint->body.width = DOWNOFFSET;
    joint->body.height = DOWNOFFSET/5;
    joint->body.x = dev->downfloor.x + (mode-1)*DOWNOFFSET + mode*dev->length;
    joint->body.y = dev->downfloor.y+DOWNOFFSET/2;
    joint->body.stroke = joint->body.height/20;

    joint->head.x = joint->body.x + mode*joint->body.width;
    joint->head.y = joint->body.y + joint->body.height/2;
    joint->head.radius = radius/4;
    joint->head.stroke = radius/10;
    joint->head.innercolor = "";
    joint->head.outercolor = "white";
}

void trigaxis(OselinDevice *dev, float radius, string m){

    Oselin_Axis *axis; int mode;
    if (m =="rear"){
        mode = 0;
        axis = &dev->rearaxis;
    }
    else{
        mode = 1;
        axis = &dev->frontaxis;
    }

    axis->body.x = dev->length*(mode+1)/3 + dev->upfloor.x;
    axis->body.y = dev->upfloor.y;
    axis->body.height = dev->height + dev->downfloor.height;
    axis->body.width = dev->height/10;
    axis->body.stroke = axis->body.width/20;
    
    axis->topscrew.innercolor = "";
    axis->topscrew.outercolor = "white";
    axis->topscrew.radius = axis->body.width /3;
    axis->topscrew.stroke = radius/10;
    axis->topscrew.x = axis->body.width/2 + axis->body.x;
    axis->topscrew.y = axis->body.width/2 + axis->body.y;
    
    
    axis->bottomscrew.innercolor = "";
    axis->bottomscrew.outercolor = "white";
    axis->bottomscrew.radius = axis->body.width /3;
    axis->bottomscrew.stroke = radius/10;
    axis->bottomscrew.x = axis->body.width/2 + axis->body.x;
    axis->bottomscrew.y = -axis->body.width/2 + axis->body.y + axis->body.height;
    axis->rotationpoint[0] = axis->body.x + axis->body.width/2;
    axis->rotationpoint[1] = axis->body.y + axis->body.height/2;
     
}

void oselin_trigonometry(OselinDevice *dev, float width, float height, float r){

    r = r *40/16;

    trigfloors(dev, width, height, "down");
    trigfloors(dev, width, height, "up");

    trigwheel(dev, height, r, "rear");
    trigwheel(dev, height, r, "front");

    trigjoint(dev, r, "rear");
    trigjoint(dev, r, "front");
    
    trigaxis(dev, r, "rear");
    trigaxis(dev, r, "front");
    
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

string oselin_to_svg(OselinDevice *device, float width, float height, int nfloors){

    string svg;

    svg = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n<svg xmlns='http://www.w3.org/2000/svg' width= '";
    svg += to_string(width) + " '  height= '";
    svg += to_string(height) + "' >";
    svg += "\n<!--#1-->";
    svg += "\n" + oselin_jointtoSVG(device->rearjoint);
    svg += "\n<!--#2-->";
    svg += "\n" + oselin_jointtoSVG(device->frontjoint);
    svg += "\n<!--#3-->";
    svg += "\n" + oselin_floortoSVG(device->downfloor);
    svg += "\n<!--#4-->";
    svg += "\n" + oselin_wheeltoSVG(device->frontwheel);
    svg += "\n<!--#5-->";
    svg += "\n" + oselin_wheeltoSVG(device->rearwheel);
    
    if (nfloors>1) {
        svg += "\n<!--#6-->";
        svg += "\n" + oselin_floortoSVG(device->upfloor);
        svg += "\n<!--#7-->";
        svg += "\n" + oselin_axistoSVG(device->rearaxis);
        svg += "\n<!--#8-->";
        svg += "\n" + oselin_axistoSVG(device->frontaxis);
    }
    svg += "\n</svg>";

    return svg;
}

string checkpoint(int i){
    return "<!--#" + to_string(i) + "-->";
}

string buffering(string svg, int i){
    int temp=0;
    string buffer;
    cout << svg[i] << endl;
    ++i;
    while (temp!=2){
        cout << buffer << endl;
        switch (svg[i])
        {
        case ' ':
            break;
        case '=':
            break;
        case '\'':
            cout << "' detected: " << temp << endl;
            temp++;
            break;
        default:
            buffer+=svg[i];
            break;
        }
        i++;
    }
    return buffer;
}

Oselin_Floor parsingfloor(string svg){
    cout << "in parsingfloor" << endl;
    string buffer;
    for (int i=0;i<svg.length();i++){
        switch (svg[i])
        {
        case 'x':
            cout << "x case detected" << endl;
            cout << buffering(svg,i);
            break;
        case 'y':
            break;
        case 'w':
            break;
        case 'h':
            break;
        case 's':
            break;
        case 'f':
            break;
        
        default:
            break;
        }
    }

}

Oselin_Wheel parsingwheel(string svg){

}

Oselin_Joint parsingjoint(string svg){

}

Oselin_Axis parsingaxis(string svg){

}

OselinDevice * oselin_parsing(string svg){
    int pieces[7][2];
    for (int i=1;i<7;i++){
        int index = svg.find(checkpoint(i));
        int len = svg.find(checkpoint(i+1)) - index;
        pieces[i-1][0] = index+10;
        pieces[i-1][1] = len-10;
    }
    cout << pieces << endl;
}