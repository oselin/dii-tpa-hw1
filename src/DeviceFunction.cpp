#include "car_trailer.h"

#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>

#define FRONT 1
#define REAR  0
#define UP    1 
#define DOWN  0


using namespace std;

string oselin::checkpoint(int i){
    if (i<9){
        return "<!--#" + to_string(i) + "-->";
    }
    else return "</svg>";
}

string oselin::buffering(string svg, string param, char symb){
    
    string buffer = "";
    int i = svg.find(param) + param.length();
    while (svg[i] != symb){
        buffer += svg[i];
        i++;
    }
    return buffer;
}

//TRIGONOMETRY SUPPORTING FUNCTIONS
oselin::Floor trigonometry_floors(oselin::Trailer *trailer, int mode){
    if (trailer!=NULL){

        oselin::Floor f;
        
        f.width(trailer->trailer_length());
        f.height(trailer->trailer_length()/15);

        trailer->trailer_height(f.height());

        f.stroke(f.height()/20);
        f.x(0);
        f.y(trailer->svg_height() - (trailer->svg_height() - trailer->height())/2 - mode*trailer->height());

        return f;
    }
    throw logic_error("Pointer is null.");
   

}

oselin::Wheel trigonometry_wheel(oselin::Trailer *trailer, int mode){
    if (trailer!=NULL){

        oselin::Wheel wheel;

        float wheeloffset = trailer->trailer_length()/12;

        wheel.radius(trailer->downfloor.height() / 40 * 2 * trailer->car_radius());
        wheel.stroke(wheel.radius()/10);
        wheel.x(trailer->downfloor.x() + pow(-1,mode)* wheeloffset + mode*trailer->trailer_length());
        wheel.y(trailer->downfloor.y() + trailer->downfloor.height() - wheel.radius()/4);
        return wheel;
    }
    throw logic_error("Pointer is null");
}

oselin::Joint trigonometry_joint(oselin::Trailer *trailer, int mode){

    if (trailer != NULL){
        oselin::Joint j;
        
        j.body.width(DOWNOFFSET);
        j.body.height(DOWNOFFSET/5);
        j.body.x(trailer->downfloor.x() + (mode-1)*DOWNOFFSET + mode*trailer->trailer_length());
        j.body.y(trailer->downfloor.y() + trailer->downfloor.height()/2 - j.body.height()/2);
        j.body.stroke(j.body.height()/20);
        
        j.head.x(j.body.x() + mode*j.body.width());
        j.head.y(j.body.y() + j.body.height()/2);
        j.head.radius(trailer->car_radius()/3);
        j.head.stroke(trailer->car_radius()/10);
        j.head.innercolor("");
        j.head.color("white");

        j.length(j.body.width() + j.head.radius());
        j.x(j.body.x());
        j.y(j.body.y());
        return j;
    }
    throw logic_error("Pointer is null");
}

oselin::Axis trigonometry_axis(oselin::Trailer *trailer, int mode){

    if (trailer != NULL){
        oselin::Axis a; 

        a.body.x(trailer->trailer_length()*(mode+1)/3 + trailer->upfloor.x());
        a.body.y(trailer->upfloor.y());
        a.body.height(trailer->height() + trailer->downfloor.height());
        a.body.width(trailer->height()/10);
        a.body.stroke(a.body.width()/20);
        
        a.top_screw.innercolor("");
        a.top_screw.color("white");
        a.top_screw.radius(a.body.width() /3);
        a.top_screw.stroke((trailer->downfloor.height() / 40 * 2 * trailer->car_radius())/10);
        a.top_screw.x(a.body.width()/2 + a.body.x());
        a.top_screw.y(a.body.width()/2 + a.body.y());
        
        
        a.bottom_screw.innercolor("");
        a.bottom_screw.color("white");
        a.bottom_screw.radius(a.body.width() /3);
        a.bottom_screw.stroke((trailer->downfloor.height() / 40 * 2 * trailer->car_radius())/10);
        a.bottom_screw.x(a.body.width()/2 + a.body.x());
        a.bottom_screw.y(-a.body.width()/2 + a.body.y() + a.body.height());
        a.point_x(a.body.x() + a.body.width()/2);
        a.point_y(a.body.y() + a.body.height()/2);
        
        a.x(a.body.x());
        a.y(a.body.y());
        return a;
    }
    throw logic_error("Pointer is null");
}

int oselin::trigonometry(oselin::Trailer *trailer, bool automaticoffset){

    if (trailer == NULL) throw logic_error("Pointer is null");

    trailer->downfloor   = trigonometry_floors(trailer, DOWN);
    trailer->rear_wheel  = trigonometry_wheel (trailer, REAR);
    trailer->front_wheel = trigonometry_wheel (trailer, FRONT);
    trailer->rear_joint  = trigonometry_joint (trailer, REAR);
    trailer->front_joint = trigonometry_joint (trailer, FRONT);
    
    if (trailer->n_floors() > 1){
        trailer->upfloor    = trigonometry_floors(trailer, (int)UP);
        trailer->rear_axis  = trigonometry_axis  (trailer, REAR);
        trailer->front_axis = trigonometry_axis  (trailer, FRONT);
    }

    trailer->x(trailer->rear_joint.head.x());
    trailer->y(trailer->rear_joint.head.y());
    trailer->length(trailer->trailer_length()+ 2*trailer->rear_joint.length() - 2* trailer->rear_joint.head.radius());
    
    if (automaticoffset){
        trailer->offset((trailer->svg_width() - trailer->downfloor.width())/2);
    }
    return 0;
}


string oselin::textToSvg(oselin::Floor line){
    float angle, val;
    if (line.width() != 4){
        angle = 0;
        val = roundf(line.width() * 100) / 100;
    }
    else{
        angle = 90;
        val = roundf(line.height() * 100) / 100;
    }
    string svg = "";

    svg += "<text x='" + to_string(line.offset() + line.x() + line.width()/2) + '\'';
    svg += " y='" + to_string(line.y() + line.height()/2 - 10) + '\'';
    svg += " fill='black' ";
    svg += "dominant-baseline='middle' text-anchor='middle' ";
    svg += "transform='rotate(" + to_string(angle) + ',' + to_string(line.offset() + line.x() + line.width()/2) +',' + to_string(line.y() + line.height()/2) +")'>";
    svg += to_string(val);
    svg += "</text>";
    return svg;
}
