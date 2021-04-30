
#include "car_trailer.h"
#include <iostream>
#include <string>
#include <cmath>


using namespace std;

/**
 * Function for handling errors. It returns a string with the error type. It is invoked by all the other functions
 * @param int error code
 **/
string errors(int c){

    switch (c)
    {
    case 0:
        return "INIT: WIDTH ERROR" ;
        break;
    case 1:
        return "INIT: STRUCTURAL ERROR" ;
        break;
    case 2:
        return "INIT: CAR DIMENSIONS ERROR" ;
        break;
    case 3:
        return "You must create/load a device first!" ;
        break;
    case 4:
        return "INIT: HEIGHT ERROR" ;
        break;
    case 5:
        return "INIT: NCARS TOO LONG" ;
        break;
    case 6:
        return "INIT: NFLOORS TOO HIGH" ;
        break;
    case 7:
        return "Check the parameters and try again" ;
        break;
    case 8:
        return "Something went wrong. " ;
        break;
    case 9:
        exit(1);
    default:
        break;
    }
    return "";
    //cout << "GOING BACK TO MAIN MENU" << endl;
}

/**
 * Check if all the data are solid
 * @param OselinDevice to be filled
 * @param float with data to check
 * @param bool for bypassing some check operations
 **/
OselinDevice *oselin_init(Parameters param, bool avoidsvg){

    OselinDevice *dev = new OselinDevice;

    //try{
    //    carlength = param[0];
    //    carheight = param[1];
    //    radius    = param[2];
    //    ncar      = param[3];
    //    nfloors   = param[4];
    //}catch(const exception& e){
    //    cout <<errors(8) << endl;
    //    return 1;
    //}
 
    if (param.radius < 16 || param.radius > 18){
        cout <<errors(7) << endl;
        return NULL;
    }

    param.length = param.length * param.ncars + (param.ncars+3)*param.length/2;
    param.height = param.height * param.nfloors + 100;

    param.margin = param.length/2;
    //CONSTRAINS
    if (!avoidsvg){
        if (param.svgwidth < param.length){
            cout <<errors(0) << endl;
            return NULL;
        }
        if (param.svgheight < param.height*5/4){
            cout <<errors(4) << endl;
            return NULL;
        }
    }
    if (param.ncars ==1 && param.nfloors == 2){
        cout <<errors(1) << endl;
        return NULL;
    }
    if (param.length < (param.height*4/5)){
        cout <<errors(2) << endl;
        return NULL;
    }
    if (param.ncars > 2){
        cout <<errors(7) << endl;
        return NULL;
    }
    if (param.nfloors > 2){
        cout <<errors(7) << endl;
        return NULL;
    }

    
    dev->param = param;
    
    return dev;

}


//TRIGONOMETRY SUPPORTING FUNCTIONS
int trigfloors(OselinDevice *dev,  string m){
    if (dev!=NULL){
        Oselin_Floor *f; int mode;
        if (m == "down") {
            mode = 0;
            f= &dev->downfloor;
        }
        else {
            mode = 1;
            f = &dev->upfloor;
        }
        f->width = dev->param.length;
        f->height = dev->param.length/15;
        f->stroke = f->height/20;
        f->x = 0;
        f->y = dev->param.svgheight - (dev->param.svgheight - dev->param.height)/2 - mode*dev->param.height;
        return 0;
    }
    else return 1;
   

}

int trigwheel(OselinDevice *dev, string m){
    if (dev!=NULL){
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
        float wheeloffset = dev->param.length/12;
        //REAR WHEEL

        wheel->radius = dev->downfloor.height / 40 * 2 * dev->param.radius;
        wheel->stroke = wheel->radius/10;
        wheel->x = dev->downfloor.x + pow(-1,mode)* wheeloffset + mode*dev->param.length;
        wheel->y = dev->downfloor.y + dev->downfloor.height - wheel->radius/4;
        return 0;
    }else return 1;
}

int trigjoint(OselinDevice *dev, string m){
    if (dev!=NULL){
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
        joint->body.x = dev->downfloor.x + (mode-1)*DOWNOFFSET + mode*dev->param.length;
        joint->body.y = dev->downfloor.y+ dev->downfloor.height/2 - joint->body.height/2;
        joint->body.stroke = joint->body.height/20;
        
        joint->head.x = joint->body.x + mode*joint->body.width;
        joint->head.y = joint->body.y + joint->body.height/2;
        joint->head.radius = dev->param.radius/3;
        joint->head.stroke =  dev->param.radius/10;
        joint->head.innercolor = "";
        joint->head.outercolor = "white";

        joint->length = joint->body.width + joint->head.radius;
        return 0;
    }else return 1;
}

int trigaxis(OselinDevice *dev, string m){
    if (dev!=NULL){
        Oselin_Axis *axis; int mode;
        if (m =="rear"){
            mode = 0;
            axis = &dev->rearaxis;
        }
        else{
            mode = 1;
            axis = &dev->frontaxis;
        }

        axis->body.x = dev->param.length*(mode+1)/3 + dev->upfloor.x;
        axis->body.y = dev->upfloor.y;
        axis->body.height = dev->param.height + dev->downfloor.height;
        axis->body.width = dev->param.height/10;
        axis->body.stroke = axis->body.width/20;
        
        axis->topscrew.innercolor = "";
        axis->topscrew.outercolor = "white";
        axis->topscrew.radius = axis->body.width /3;
        axis->topscrew.stroke = (dev->downfloor.height / 40 * 2 * dev->param.radius)/10;
        axis->topscrew.x = axis->body.width/2 + axis->body.x;
        axis->topscrew.y = axis->body.width/2 + axis->body.y;
        
        
        axis->bottomscrew.innercolor = "";
        axis->bottomscrew.outercolor = "white";
        axis->bottomscrew.radius = axis->body.width /3;
        axis->bottomscrew.stroke = (dev->downfloor.height / 40 * 2 * dev->param.radius)/10;
        axis->bottomscrew.x = axis->body.width/2 + axis->body.x;
        axis->bottomscrew.y = -axis->body.width/2 + axis->body.y + axis->body.height;
        axis->rotationpoint[0] = axis->body.x + axis->body.width/2;
        axis->rotationpoint[1] = axis->body.y + axis->body.height/2;
        return 0;
    }else return 1;
     
}

/**
 * Do all the math for OselinDevice struct
 * @param OselinDevice to be calculated
 * @param bool for set automatically the offset for centering the drawing
 **/
int oselin_trigonometry(OselinDevice *dev, bool automaticoffset){

    if (dev == NULL){
        cout <<errors(9) << endl;
        return 1;
    }

    trigfloors(dev, "down");

   
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
    dev->abslength = dev->param.length + 2*dev->rearjoint.length - 2* dev->rearjoint.head.radius;
    if (automaticoffset){
        dev->offset = (dev->param.svgwidth - dev->downfloor.width)/2;
    }
    return 0;
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
    str = oselin_floortoSVG(joint.body,offset) + oselin_wheeltoSVG(joint.head, offset);
    return str;
}

string oselin_texttosvg(Oselin_Floor el, float offset){
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
    svg += "<text x='" + to_string(offset + el.x + el.width/2) + '\'';
    svg += " y='" + to_string(el.y + el.height/2 - 10) + '\'';
    svg += " fill='black' ";
    svg += "dominant-baseline='middle' text-anchor='middle' ";
    svg += "transform='rotate(" + to_string(angle) + ',' + to_string(offset + el.x + el.width/2) +',' + to_string(el.y + el.height/2) +")'>";
    svg += to_string(val);
    svg += "</text>";
    return svg;
}

string oselin_measures(OselinDevice dev){
    string measures;
    float offset = dev.offset;

    if (dev.param.nfloors > 1){
    //TOTAL HEIGHT
        Oselin_Floor m;
        m.x = dev.upfloor.x - dev.rearjoint.length * 5/4;
        m.y = dev.upfloor.y;
        m.width = 4;
        m.height = dev.param.height + dev.downfloor.height;
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

        measures += "\n" + oselin_floortoSVG(m, offset);
        measures += "\n" + oselin_floortoSVG(m12, offset);
        measures += "\n" + oselin_floortoSVG(m13, offset);
        measures += "\n" + oselin_texttosvg(m, offset);
    }
    //TOTAL LENGTH
    Oselin_Floor m2;
    m2.x = dev.downfloor.x;
    if (dev.param.nfloors > 1) m2.y = dev.upfloor.y - 3 * dev.downfloor.height;
    else m2.y = dev.downfloor.y - 3 * dev.downfloor.height;
    m2.width = dev.param.length;
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

    measures += "\n" + oselin_floortoSVG(m2, offset);
    measures += "\n" + oselin_floortoSVG(m14, offset);
    measures += "\n" + oselin_floortoSVG(m15, offset);
    measures += "\n" + oselin_texttosvg(m2, offset);

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

    measures += "\n" + oselin_floortoSVG(m3, offset);
    measures += "\n" + oselin_floortoSVG(m10, offset);
    measures += "\n" + oselin_floortoSVG(m11, offset);
    measures += "\n" + oselin_texttosvg(m3, offset);

    if (dev.param.nfloors > 1){
    //HEIGHT
        Oselin_Floor m4;
        m4.x = dev.upfloor.x + dev.param.length + 5/4*dev.frontjoint.length;
        m4.y = dev.upfloor.y + dev.upfloor.height;
        m4.width = 4;
        m4.height = dev.param.height - dev.upfloor.height;
        m4.fillingcolor = "black";
        m4.stroke = 0;
        m4.strokecolor = "";

        Oselin_Floor m6;
        m6.x = dev.upfloor.x + dev.param.length;
        m6.y = dev.upfloor.y + dev.upfloor.height;
        m6.width = dev.frontjoint.length * 5/4;
        m6.height = 1;
        m6.fillingcolor = "black";
        m6.stroke = 0;
        m6.strokecolor = "";

        Oselin_Floor m7;
        m7.x = dev.upfloor.x + dev.param.length;
        m7.y = dev.downfloor.y;
        m7.width = dev.frontjoint.length * 5/4;
        m7.height = 1;
        m7.fillingcolor = "black";
        m7.stroke = 0;
        m7.strokecolor = "";

        measures += "\n" + oselin_floortoSVG(m4, offset);
        measures += "\n" + oselin_floortoSVG(m6, offset);
        measures += "\n" + oselin_floortoSVG(m7, offset);
        measures += "\n" + oselin_texttosvg(m4, offset);
    }
    //JOINT LENGTH
    Oselin_Floor m5;
    m5.x = dev.downfloor.x + dev.param.length;
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

    measures += "\n" + oselin_floortoSVG(m5, offset);
    measures += "\n" + oselin_floortoSVG(m8, offset);
    measures += "\n" + oselin_floortoSVG(m9, offset);
    measures += "\n" + oselin_texttosvg(m5, offset);

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

    measures += "\n" + oselin_floortoSVG(m16, offset);
    measures += "\n" + oselin_floortoSVG(m17, offset);
    measures += "\n" + oselin_floortoSVG(m18, offset);
    measures += "\n" + oselin_texttosvg(m16, offset);
    
    
    
    return measures;
}

/**
 * Convert the device into a string
 * @param OselinDevice to convert
 * @param bool for adding or not the header
 * @param bool to add or not measures
 **/
int oselin_to_svg(OselinDevice *device, bool with_header, bool with_measures){
    cout << device->param.svgwidth << endl;
    string svg;
    if (device!=NULL){
        if (with_header){
        svg = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n<svg xmlns='http://www.w3.org/2000/svg' width='";
        svg += to_string(device->param.svgwidth) + " '  height='";
        svg += to_string(device->param.svgheight) + "' >";

        svg += "<rect  x='0.000000' y='0.000000' width='" + to_string(device->param.svgwidth) + "' height='" + to_string(device->param.svgheight) + "' style='stroke-width:0.0; stroke:' fill='white' />";
        }
        svg += "\n<!--#1-->";
        svg += "\n" + oselin_jointtoSVG(device->rearjoint, device->offset);
        svg += "\n<!--#2-->";
        svg += "\n" + oselin_jointtoSVG(device->frontjoint, device->offset);
        svg += "\n<!--#3-->";
        svg += "\n" + oselin_floortoSVG(device->downfloor, device->offset);
        svg += "\n<!--#4-->";
        svg += "\n" + oselin_wheeltoSVG(device->frontwheel, device->offset);
        svg += "\n<!--#5-->";
        svg += "\n" + oselin_wheeltoSVG(device->rearwheel, device->offset);
        
        if (device->param.nfloors > 1) {
            svg += "\n<!--#6-->";
            svg += "\n" + oselin_floortoSVG(device->upfloor, device->offset);
            svg += "\n<!--#7-->";
            svg += "\n" + oselin_axistoSVG(device->rearaxis, device->offset);
            svg += "\n<!--#8-->";
            svg += "\n" + oselin_axistoSVG(device->frontaxis, device->offset);
        }
        
        if (with_measures){
            svg += oselin_measures((*device));
        }

        
        device->svg = svg;
        return 0;
    }else return 1;
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

/**
 * Parse an svg imported as string and fill the device
 * @param string svg
 * @param device to be filled
 **/
void oselin_parsing(OselinDevice * device, string svg){
    if (svg!=""){
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
        device->param.length = device->downfloor.width;
        device->param.height = (float)(device->downfloor.y - device->upfloor.y  - 100) /device->param.nfloors;
        
        device->param.ncars = (int)(device->param.length/4.5);
        cout << device->param.height << endl;
        Parameters p;
        p.length = (float)(device->param.length/4.5);
        p.height = device->param.height;
        p.radius = 20 * device->rearwheel.radius/device->downfloor.height;
        p.ncars = 2;
        p.nfloors = (float)device->param.nfloors;

        p.svgwidth  = device->param.svgwidth ;  
        p.svgheight = device->param.svgheight;

        OselinDevice *dev = oselin_init(p);
        if (dev!= NULL){
            oselin_trigonometry(dev);
            (*device) = (*dev);
        }
    }
    else device->svg = "";
}


/**
 * Allow changing in the device
 **/
OselinDevice *oselin_set(OselinDevice *dev, int index, float newvalue){

    OselinDevice *set = new OselinDevice;
    Parameters array;
    array = dev->param;

    array.length = dev->param.length/((float)dev->param.ncars + ((float)dev->param.ncars+3)/2);
    array.height = (dev->param.height -100)/dev->param.nfloors;
    //if (index != -1 ) array[index] = newvalue;
    set = oselin_init(array);
    if (set !=NULL){
        oselin_trigonometry(set);
        return set;
    }
    else return NULL;

}

/**
 * Return device-like struct allowing several copies
 * @param device (=trailer already existing)
 **/
OselinDevice *oselin_init_acopyof(OselinDevice *dev){
    if (dev != NULL){
        OselinDevice *copy = oselin_init(dev->param, true);
        if (copy != NULL) oselin_trigonometry(copy);
        return copy;
    }
    else return NULL;
}