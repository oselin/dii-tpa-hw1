
#include "car_trailer.h"
#include <iostream>
#include <string>
#include <cmath>



using namespace std;/*
 *  Source for the not-part-of-a-library class Fraction
 *
 */

void errors(int c){

    switch (c)
    {
    case 0:
        cout << "INIT: WIDTH ERROR, ";
        break;
    case 1:
        cout << "INIT: STRUCTURAL ERROR, ";
        break;
    case 2:
        cout << "INIT: CAR DIMENSIONS ERROR, ";
        break;
    case 3:
        cout << "You must create/load a device first!, ";
        break;
    case 4:
        cout << "INIT: HEIGHT ERROR, ";
        break;
    case 5:
        cout << "INIT: NCARS TOO LONG, ";
        break;
    case 6:
        cout << "INIT: NFLOORS TOO HIGH, ";
        break;
    default:
        break;
    }
    cout << "GOING BACK TO MAIN MENU" << endl;
}
int oselin_init(OselinDevice *dev, float carlength, float carheight, int ncar, int nfloors, float radius){

    float margin = dev->param.svgwidth/10;
    int tempcar, tempfloor;
    float tempradius, templength, tempheight;
    if (ncar != -1) tempcar = ncar;
    else tempcar = dev->param.ncars;

    if (nfloors != -1) tempfloor = nfloors;
    else tempfloor = dev->param.nfloors;

    if (radius != -1) tempradius = radius;
    else tempradius = dev->param.radius;

    if (carlength != -1) templength = carlength * tempcar + (tempcar+1)*margin;
    else templength = dev->length;
    if (carheight != -1) tempheight = carheight * tempfloor + 100;
    else tempheight = dev->height;

    if (dev->param.svgwidth < templength){
        errors(0);
        return 1;
    }

    if (dev->param.svgheight < tempheight*5/4){
        errors(4);
        return 1;
    }

    if (ncar ==1 && tempfloor == 2){
        errors(1);
        return 1;
    }
    if (templength < (tempheight*4/5)){
        errors(2);
        return 1;
    }
    if (tempcar > 2){
        errors(5);
        return 1;
    }
    if (tempfloor > 2){
        errors(6);
        return 1;
    }
    
    dev->param.ncars = tempcar;
    dev->param.nfloors = tempfloor;
    dev->param.radius = tempradius;
    dev->length = templength;
    dev->height = tempheight;
    
    return 0;

}


//TRIGONOMETRY SUPPORTING FUNCTIONS
void trigfloors(OselinDevice *dev,  string m){

    Oselin_Floor *f; int mode;
    if (m == "down") {
        mode = 0;
        f= &dev->downfloor;
    }
    else {
        mode = 1;
        f = &dev->upfloor;
    }
    f->x = (dev->param.svgwidth-dev->length)/2;
    f->y = (dev->param.svgheight-2*DOWNOFFSET) - mode*dev->height;
    f->width = dev->length;
    f->height = dev->param.svgheight/10;
    f->stroke = f->height/20;

}
void trigwheel(OselinDevice *dev, string m){
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
    wheel->y = dev->param.svgheight-DOWNOFFSET;
    wheel->radius = dev->param.radius;
    wheel->stroke = dev->param.radius/10;
}
void trigjoint(OselinDevice *dev, string m){

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
    joint->head.radius = dev->param.radius/4;
    joint->head.stroke = dev->param.radius/10;
    joint->head.innercolor = "";
    joint->head.outercolor = "white";
}
void trigaxis(OselinDevice *dev, string m){

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
    axis->topscrew.stroke = dev->param.radius/10;
    axis->topscrew.x = axis->body.width/2 + axis->body.x;
    axis->topscrew.y = axis->body.width/2 + axis->body.y;
    
    
    axis->bottomscrew.innercolor = "";
    axis->bottomscrew.outercolor = "white";
    axis->bottomscrew.radius = axis->body.width /3;
    axis->bottomscrew.stroke = dev->param.radius/10;
    axis->bottomscrew.x = axis->body.width/2 + axis->body.x;
    axis->bottomscrew.y = -axis->body.width/2 + axis->body.y + axis->body.height;
    axis->rotationpoint[0] = axis->body.x + axis->body.width/2;
    axis->rotationpoint[1] = axis->body.y + axis->body.height/2;
     
}

void oselin_trigonometry(OselinDevice *dev){

    dev->param.radius = dev->param.radius *40/16;

    trigfloors(dev, "down");
    trigfloors(dev, "up");

    trigwheel(dev, "rear");
    trigwheel(dev, "front");

    trigjoint(dev, "rear");
    trigjoint(dev, "front");
    
    trigaxis(dev, "rear");
    trigaxis(dev, "front");
    
}

//STRING TO SVG: SUPPORTING FUNCTIONS
string oselin_wheeltoSVG(Oselin_Wheel wheel){
    string str;
    str += "\n<circle";
    str += " cx='" + to_string(wheel.x) + "'";
    str += " cy='" + to_string(wheel.y) + "'";
    str += " r='" + to_string(wheel.radius) + "'";
    str += " stroke='" + wheel.strokecolor + "'";
    str += " stroke-width='" + to_string(wheel.stroke) + "'";
    str += " fill='" + wheel.outercolor + "'";
    str += " />";

    if (wheel.innercolor != ""){
        str += "\n<circle";
        str += " cx='" + to_string(wheel.x) + "'";
        str += " cy='" + to_string(wheel.y) + "'";
        str += " r='" + to_string(wheel.radius*3/4) + "'";
        str += " stroke='" + wheel.strokecolor + "'";
        str += " stroke-width='" + to_string(wheel.stroke) + "'";
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
    str += " style='stroke-width:" + to_string(floor.stroke) + ";";
    str += " stroke:" + floor.strokecolor + "'";
    str += " fill='" + floor.fillingcolor + "'";
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

string oselin_to_svg(OselinDevice *device){

    string svg;

    svg = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n<svg xmlns='http://www.w3.org/2000/svg' width='";
    svg += to_string(device->param.svgwidth) + " '  height='";
    svg += to_string(device->param.svgheight) + "' >";
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
    
    if (device->param.nfloors>1) {
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

//STRING PARSING: SUPPORTING FUNCTIONS
string checkpoint(int i){
    if (i<9){
        return "<!--#" + to_string(i) + "-->";
    }
    else return "</svg>";
}
string buffering(string svg, string param, char symb){
    
    string buffer = "";
    int i = svg.find(param) + param.length();
    while (svg[i] != symb){
        buffer += svg[i];
        i++;
    }
    return buffer;
}
Oselin_Floor parsingfloor(string svg){
    Oselin_Floor f;

    f.x = stof(buffering(svg, "x='",'\''));
    f.y = stof(buffering(svg, "y='",'\''));
    f.width = stof(buffering(svg, "width='",'\''));
    f.height = stof(buffering(svg, "height='",'\''));
    f.fillingcolor = buffering(svg, "fill='",'\'');
    f.stroke = stof(buffering(svg, "stroke-width:",';'));
    f.strokecolor = buffering(svg, "stroke:", '\'');
    
    return f;    
}
Oselin_Wheel parsingwheel(string svg, int doublecolor){
    Oselin_Wheel w;
    w.x = stof(buffering(svg, "cx='",'\''));
    w.y = stof(buffering(svg, "cy='",'\''));
    w.radius = stof(buffering(svg, "r='",'\''));
    w.stroke = stof(buffering(svg, "stroke-width='",'\''));
    w.strokecolor = buffering(svg, "stroke='",'\'');
    w.outercolor = buffering(svg, "fill='",'\'');

    if (doublecolor) w.innercolor = buffering(svg, "fill= '",'\'');
    else w.innercolor = "";

    return w;

}
Oselin_Joint parsingjoint(string svg){

    Oselin_Joint j;
    
    string rect = svg.substr(svg.find("<rect"),svg.find(">")-svg.find("<rect"));
    string circle = svg.substr(svg.find("<circle"),svg.find(">")-svg.find("<circle"));

    j.body = parsingfloor(rect);
    j.head = parsingwheel(circle,0);
    
    return j;
}
Oselin_Axis parsingaxis(string svg){

    Oselin_Axis a;
    
    string rect = svg.substr(svg.find("<rect"),svg.find(">")-svg.find("<rect"));
    int index = svg.find("<circle");
    int index2 = svg.find("<circle",index+1);
    string circlebottom = svg.substr(index,svg.find(">") - index);
    string circletop = svg.substr(index2,svg.find(">",index2) - index2);
    string rotation = "<g transform='rotate(";
    a.angle = stof(buffering(svg,rotation,','));
    rotation += to_string(a.angle) + ',';

    for (int i=0;i<2;i++){
        if (!i) a.rotationpoint[i] = stof(buffering(svg, rotation, ','));
        else a.rotationpoint[i] = stof(buffering(svg, rotation, ')'));
        rotation += to_string(a.rotationpoint[i]) + ',';
    }
    a.body = parsingfloor(rect);
    a.bottomscrew = parsingwheel(circlebottom,0);
    a.topscrew  = parsingwheel(circletop,0);

    return a;
    
}

void oselin_parsing(OselinDevice * device, string svg){

    int pieces[7][2];
    for (int i=1;i<9;i++){
        int index = svg.find(checkpoint(i));
        int len = svg.find(checkpoint(i+1)) - index;
        pieces[i-1][0] = index+11;
        pieces[i-1][1] = len-11;
    }
    device->param.svgwidth = stof(buffering(svg.substr(0,pieces[0][0]),"width='",'\''));
    device->param.svgheight = stof(buffering(svg.substr(0,pieces[0][0]),"height='",'\''));
    device->rearjoint = parsingjoint(svg.substr(pieces[0][0], pieces[0][1]));
    device->frontjoint = parsingjoint(svg.substr(pieces[1][0], pieces[1][1]));
    device->downfloor = parsingfloor(svg.substr(pieces[2][0], pieces[2][1]));
    device->frontwheel = parsingwheel(svg.substr(pieces[3][0], pieces[3][1]),1);
    device->rearwheel = parsingwheel(svg.substr(pieces[4][0], pieces[4][1]),1);
    device->upfloor = parsingfloor(svg.substr(pieces[5][0], pieces[5][1]));
    device->rearaxis = parsingaxis(svg.substr(pieces[6][0], pieces[6][1]));
    device->frontaxis = parsingaxis(svg.substr(pieces[7][0], pieces[7][1]));
    device->length = device->downfloor.width;
    device->height = 10 * device->downfloor.height;
}


//MY_SET REQUIRED FUNCTIONS
int oselin_set_carlength(OselinDevice *dev, float len){
    return oselin_init(dev, len, -1, -1, -1, -1);
}

int oselin_set_carheight(OselinDevice *dev, float height){
    return oselin_init(dev, -1, height, -1, -1, -1);
}

int oselin_set_radius(OselinDevice *dev, float r){
    return oselin_init(dev, -1, -1, -1, -1, r);
}

int oselin_set_floornumb(OselinDevice *dev, int nfloors){
    return oselin_init(dev, -1, -1, -1, nfloors, -1);
}

int oselin_set_carnumb(OselinDevice *dev, int ncars){
    return oselin_init(dev, -1, -1, ncars, -1, -1);
    
}