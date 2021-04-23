
#include "car_trailer.h"
#include <iostream>
#include <string>
#include <cmath>



using namespace std;

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

    float margin = carlength/2;
    int tempcar, tempfloor;
    float tempradius, templength, tempheight;

    if (ncar != -1) tempcar = ncar;
    else tempcar = dev->param.ncars;

    if (nfloors != -1) tempfloor = nfloors;
    else tempfloor = dev->param.nfloors;

    if (radius != -1) tempradius = radius;
    else tempradius = dev->param.radius;

    if (carlength != -1) templength = carlength * tempcar + (tempcar+3)*margin;
    else templength = dev->length;
    if (carheight != -1) tempheight = carheight * tempfloor + 100;
    else tempheight = dev->height;

    //CONSTRAINS
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
    f->width = dev->length;
    f->height = dev->length/15;
    f->stroke = f->height/20;
    f->x = 0;
    f->y = dev->param.svgheight - (dev->param.svgheight - dev->height)/2 - mode*dev->height;
   

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
    wheel->radius = dev->param.radius;
    wheel->stroke = dev->param.radius/10;
    wheel->x = dev->downfloor.x + pow(-1,mode)* wheeloffset + mode*dev->length;
    wheel->y = dev->downfloor.y + dev->downfloor.height - wheel->radius/4;
    
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
    joint->body.y = dev->downfloor.y+ dev->downfloor.height/2 - joint->body.height/2;
    joint->body.stroke = joint->body.height/20;

    joint->head.x = joint->body.x + mode*joint->body.width;
    joint->head.y = joint->body.y + joint->body.height/2;
    joint->head.radius = dev->param.radius/3;
    joint->head.stroke =  dev->param.radius/10;
    joint->head.innercolor = "";
    joint->head.outercolor = "white";

    joint->length = joint->body.width + joint->head.radius;
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

    trigfloors(dev, "down");

    dev->param.radius = dev->downfloor.height / 40 * 2 * dev->param.radius;
    trigwheel(dev, "rear");
    trigwheel(dev, "front");

    trigjoint(dev, "rear");
    trigjoint(dev, "front");
    
    if (dev->param.nfloors > 1){
        trigfloors(dev, "up");
        trigaxis(dev, "rear");
        trigaxis(dev, "front");
    }

    dev->absx = dev->rearjoint.head.x;
    dev->absy = dev->rearjoint.head.y;
    dev->abslength = dev->length + 2*dev->rearjoint.length - 2* dev->rearjoint.head.radius;
    
}

//STRING TO SVG: SUPPORTING FUNCTIONS
string oselin_wheeltoSVG(Oselin_Wheel wheel, float offset){
    string str;
    str += "\n<circle";
    str += " cx='" + to_string(offset + wheel.x) + "'";
    str += " cy='" + to_string(wheel.y) + "'";
    str += " r='" + to_string(wheel.radius) + "'";
    str += " stroke='" + wheel.strokecolor + "'";
    str += " stroke-width='" + to_string(wheel.stroke) + "'";
    str += " fill='" + wheel.outercolor + "'";
    str += " />";

    if (wheel.innercolor != ""){
        str += "\n<circle";
        str += " cx='" + to_string(offset + wheel.x) + "'";
        str += " cy='" + to_string(wheel.y) + "'";
        str += " r='" + to_string(wheel.radius*3/4) + "'";
        str += " stroke='" + wheel.strokecolor + "'";
        str += " stroke-width='" + to_string(wheel.stroke) + "'";
        str += " fill= '" + wheel.innercolor + "'";
        str += " />";   
    }
    return str;
}

string oselin_floortoSVG(Oselin_Floor floor, float offset){
    string str = "\n<rect  ";
    str += "x='" + to_string(offset + floor.x) + "'";
    str += " y='" + to_string(floor.y) + "'";
    str += " width='" + to_string(floor.width) + "'";
    str += " height='" + to_string(floor.height) + "'";
    str += " style='stroke-width:" + to_string(floor.stroke) + ";";
    str += " stroke:" + floor.strokecolor + "'";
    str += " fill='" + floor.fillingcolor + "'";
    str += " />";
    return str;
}

string oselin_axistoSVG(Oselin_Axis steel, float offset){
    string str = "\n<g transform='rotate(";
    str += to_string(steel.angle) + "," + to_string(offset + steel.rotationpoint[0]) + "," + to_string(steel.rotationpoint[1]);
    str += ")'>";
    str += oselin_floortoSVG(steel.body, offset);
    
    str += oselin_wheeltoSVG(steel.bottomscrew, offset) + oselin_wheeltoSVG(steel.topscrew, offset);
    str += "\n</g>";
    return str;
}

string oselin_jointtoSVG(Oselin_Joint joint, float offset){
    string str;
    str = oselin_floortoSVG(joint.body, offset) + oselin_wheeltoSVG(joint.head, offset);
    return str;
}

string oselin_texttosvg(Oselin_Floor el){
    float angle, val;
    if (el.width != 4){
        angle = 0;
        val = roundf(el.width * 100) / 100;
    }
    else{
        angle = 90;
        val = roundf(el.height * 100) / 100;
    }
    string svg = "";
    svg += "<text x='" + to_string(el.x + el.width/2) + '\'';
    svg += " y='" + to_string(el.y + el.height/2 - 10) + '\'';
    svg += " fill='black' ";
    svg += "dominant-baseline='middle' text-anchor='middle' ";
    svg += "transform='rotate(" + to_string(angle) + ',' + to_string(el.x + el.width/2) +',' + to_string(el.y + el.height/2) +")'>";
    svg += to_string(val);
    svg += "</text>";
    return svg;
}

string oselin_measures(OselinDevice dev){
    string measures;

    if (dev.param.nfloors > 1){
    //TOTAL HEIGHT
        Oselin_Floor m;
        m.x = dev.upfloor.x - dev.rearjoint.length * 5/4;
        m.y = dev.upfloor.y;
        m.width = 4;
        m.height = dev.height + dev.downfloor.height;
        m.fillingcolor = "black";
        m.stroke = 0;
        m.strokecolor = "";

        Oselin_Floor m12;
        m12.x = m.x - dev.rearjoint.length/4;
        m12.y = m.y;
        m12.width = dev.rearjoint.length*6/4;
        m12.height = 1;
        m12.fillingcolor = "black";
        m12.stroke = 0;
        m12.strokecolor = "";

        Oselin_Floor m13;
        m13.x = m.x - dev.rearjoint.length/4;
        m13.y = m.y + m.height;
        m13.width = dev.rearjoint.length*6/4;
        m13.height = 1;
        m13.fillingcolor = "black";
        m13.stroke = 0;
        m13.strokecolor = "";

        measures += "\n" + oselin_floortoSVG(m, 0);
        measures += "\n" + oselin_floortoSVG(m12, 0);
        measures += "\n" + oselin_floortoSVG(m13, 0);
        measures += "\n" + oselin_texttosvg(m);
    }
    //TOTAL LENGTH
    Oselin_Floor m2;
    m2.x = dev.downfloor.x;
    if (dev.param.nfloors > 1) m2.y = dev.upfloor.y - 3 * dev.downfloor.height;
    else m2.y = dev.downfloor.y - 3 * dev.downfloor.height;
    m2.width = dev.length;
    m2.height = 4;
    m2.fillingcolor = "black";
    m2.stroke = 0;
    m2.strokecolor = "";

    Oselin_Floor m14;
    m14.x = m2.x;
    m14.y = m2.y*0.95;
    m14.width = 1;
    m14.height = 4 * dev.downfloor.height;
    m14.fillingcolor = "black";
    m14.stroke = 0;
    m14.strokecolor = "";

    Oselin_Floor m15;
    m15.x = m2.x + m2.width;
    m15.y = m2.y*0.95;
    m15.width = 1;
    m15.height = 4 * dev.downfloor.height;
    m15.fillingcolor = "black";
    m15.stroke = 0;
    m15.strokecolor = "";

    measures += "\n" + oselin_floortoSVG(m2, 0);
    measures += "\n" + oselin_floortoSVG(m14, 0);
    measures += "\n" + oselin_floortoSVG(m15, 0);
    measures += "\n" + oselin_texttosvg(m2);

    //OUTER RADIUS
    Oselin_Floor m3;
    m3.x = dev.rearwheel.x - dev.rearwheel.radius;
    m3.y = dev.rearwheel.y + 2*dev.rearwheel.radius;
    m3.width = 2* dev.rearwheel.radius;
    m3.height = 4;
    m3.fillingcolor = "black";
    m3.stroke = 0;
    m3.strokecolor = "";

    Oselin_Floor m10;
    m10.x = m3.x;
    m10.y = dev.downfloor.y + dev.downfloor.height;
    m10.width = 1;
    m10.height = 2*dev.rearwheel.radius;
    m10.fillingcolor = "black";
    m10.stroke = 0;
    m10.strokecolor = "";

    Oselin_Floor m11;
    m11.x = m3.x + 2*dev.frontwheel.radius;
    m11.y = dev.downfloor.y + dev.downfloor.height;
    m11.width = 1;
    m11.height = 2*dev.rearwheel.radius;
    m11.fillingcolor = "black";
    m11.stroke = 0;
    m11.strokecolor = "";

    measures += "\n" + oselin_floortoSVG(m3, 0);
    measures += "\n" + oselin_floortoSVG(m10, 0);
    measures += "\n" + oselin_floortoSVG(m11, 0);
    measures += "\n" + oselin_texttosvg(m3);

    if (dev.param.nfloors > 1){
    //HEIGHT
        Oselin_Floor m4;
        m4.x = dev.upfloor.x + dev.length + 5/4*dev.frontjoint.length;
        m4.y = dev.upfloor.y + dev.upfloor.height;
        m4.width = 4;
        m4.height = dev.height - dev.upfloor.height;
        m4.fillingcolor = "black";
        m4.stroke = 0;
        m4.strokecolor = "";

        Oselin_Floor m6;
        m6.x = dev.upfloor.x + dev.length;
        m6.y = dev.upfloor.y + dev.upfloor.height;
        m6.width = dev.frontjoint.length * 5/4;
        m6.height = 1;
        m6.fillingcolor = "black";
        m6.stroke = 0;
        m6.strokecolor = "";

        Oselin_Floor m7;
        m7.x = dev.upfloor.x + dev.length;
        m7.y = dev.downfloor.y;
        m7.width = dev.frontjoint.length * 5/4;
        m7.height = 1;
        m7.fillingcolor = "black";
        m7.stroke = 0;
        m7.strokecolor = "";

        measures += "\n" + oselin_floortoSVG(m4, 0);
        measures += "\n" + oselin_floortoSVG(m6, 0);
        measures += "\n" + oselin_floortoSVG(m7, 0);
        measures += "\n" + oselin_texttosvg(m4);
    }
    //JOINT LENGTH
    Oselin_Floor m5;
    m5.x = dev.downfloor.x + dev.length;
    m5.y = dev.frontwheel.y + 2*dev.frontwheel.radius;
    m5.width = dev.frontjoint.length;
    m5.height = 4;
    m5.fillingcolor = "black";
    m5.stroke = 0;
    m5.strokecolor = "";

    Oselin_Floor m8;
    m8.x = m5.x;
    m8.y = dev.downfloor.y + dev.downfloor.height;
    m8.width = 1;
    m8.height = 2*dev.rearwheel.radius;
    m8.fillingcolor = "black";
    m8.stroke = 0;
    m8.strokecolor = "";

    Oselin_Floor m9;
    m9.x = m5.x + dev.frontjoint.length;
    m9.y = dev.downfloor.y + dev.downfloor.height/2;
    m9.width = 1;
    m9.height = 2*dev.rearwheel.radius + dev.downfloor.height/2;
    m9.fillingcolor = "black";
    m9.stroke = 0;
    m9.strokecolor = "";

    measures += "\n" + oselin_floortoSVG(m5, 0);
    measures += "\n" + oselin_floortoSVG(m8, 0);
    measures += "\n" + oselin_floortoSVG(m9, 0);
    measures += "\n" + oselin_texttosvg(m5);

    //FLOOR HEIGHT
    Oselin_Floor m16;
    m16.x = dev.downfloor.x - dev.rearjoint.length * 8/4;
    m16.y = dev.downfloor.y;
    m16.width = 4;
    m16.height = dev.downfloor.height;
    m16.fillingcolor = "black";
    m16.stroke = 0;
    m16.strokecolor = "";

    Oselin_Floor m17;
    m17.x = m16.x - dev.rearjoint.length/4;
    m17.y = m16.y;
    m17.width = dev.rearjoint.length*9/4;
    m17.height = 1;
    m17.fillingcolor = "black";
    m17.stroke = 0;
    m17.strokecolor = "";

    Oselin_Floor m18;
    m18.x = m16.x - dev.rearjoint.length/4;
    m18.y = m16.y + dev.downfloor.height;
    m18.width = dev.rearjoint.length*9/4;
    m18.height = 1;
    m18.fillingcolor = "black";
    m18.stroke = 0;
    m18.strokecolor = "";

    measures += "\n" + oselin_floortoSVG(m16, 0);
    measures += "\n" + oselin_floortoSVG(m17, 0);
    measures += "\n" + oselin_floortoSVG(m18, 0);
    measures += "\n" + oselin_texttosvg(m16);
    
    
    
    return measures;
}

string oselin_to_svg(OselinDevice *device, bool with_header, bool with_measures, float offset = 0){

    string svg;
    if (with_header){
    svg = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n<svg xmlns='http://www.w3.org/2000/svg' width='";
    svg += to_string(device->param.svgwidth) + " '  height='";
    svg += to_string(device->param.svgheight) + "' >";

    svg += "<rect  x='0.000000' y='0.000000' width='" + to_string(device->param.svgwidth) + "' height='" + to_string(device->param.svgheight) + "' style='stroke-width:0.0; stroke:' fill='white' />";
    }
    svg += "\n<!--#1-->";
    svg += "\n" + oselin_jointtoSVG(device->rearjoint, offset);
    svg += "\n<!--#2-->";
    svg += "\n" + oselin_jointtoSVG(device->frontjoint, offset);
    svg += "\n<!--#3-->";
    svg += "\n" + oselin_floortoSVG(device->downfloor, offset);
    svg += "\n<!--#4-->";
    svg += "\n" + oselin_wheeltoSVG(device->frontwheel, offset);
    svg += "\n<!--#5-->";
    svg += "\n" + oselin_wheeltoSVG(device->rearwheel, offset);
    
    if (device->param.nfloors > 1) {
        svg += "\n<!--#6-->";
        svg += "\n" + oselin_floortoSVG(device->upfloor, offset);
        svg += "\n<!--#7-->";
        svg += "\n" + oselin_axistoSVG(device->rearaxis, offset);
        svg += "\n<!--#8-->";
        svg += "\n" + oselin_axistoSVG(device->frontaxis, offset);
    }
    
    if (with_measures){
        svg += oselin_measures((*device));
    }

    

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

Oselin_Floor parsingfloor(string svg, int mode){
    Oselin_Floor f;
    if (mode) cout << svg << endl;
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

    j.body = parsingfloor(rect,0);
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
    a.body = parsingfloor(rect,0);
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
    device->downfloor = parsingfloor(svg.substr(pieces[2][0], pieces[2][1]),0);
    device->frontwheel = parsingwheel(svg.substr(pieces[3][0], pieces[3][1]),1);
    device->rearwheel = parsingwheel(svg.substr(pieces[4][0], pieces[4][1]),1);

    if (pieces[5][1] > 0){
        device->upfloor = parsingfloor(svg.substr(pieces[5][0], pieces[5][1]),0);
        device->rearaxis = parsingaxis(svg.substr(pieces[6][0], pieces[6][1]));
        device->frontaxis = parsingaxis(svg.substr(pieces[7][0], pieces[7][1]));
        device->param.nfloors = 2;
    }
    else device->param.nfloors = 1;
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