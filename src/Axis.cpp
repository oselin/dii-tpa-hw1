#include "car_trailer.h"

#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>

using namespace std;

//Constructor
oselin::Axis::Axis(): oselin::Svg(){
    this->angle_ = 20;
}

//Copy Constructor
oselin::Axis::Axis(Axis &a): oselin::Svg(a){
    this->body =         a.body;
    this->bottom_screw = a.bottom_screw;
    this->top_screw =    a.top_screw;
    this->angle_ =       a.angle();
    this->point_[0]=     a.point()[0];
    this->point_[1]=     a.point()[1];
}

//Constructor - PARSING
oselin::Axis::Axis(string svg){
    string rect = svg.substr(svg.find("<rect"),svg.find(">")-svg.find("<rect"));
    int index = svg.find("<circle");
    int index2 = svg.find("<circle",index+1);
    string circlebottom = svg.substr(index,svg.find(">") - index);
    string circletop = svg.substr(index2,svg.find(">",index2) - index2);
    string rotation = "<g transform='rotate(";
    this->angle_ = stof(oselin::buffering(svg,rotation,','));
    rotation += to_string(this->angle_) + ',';

    for (int i=0;i<2;i++){
        if (!i) this->point_[i] = stof(oselin::buffering(svg, rotation, ','));
        else    this->point_[i] = stof(oselin::buffering(svg, rotation, ')'));
        rotation += to_string(this->point_[i]) + ',';
    }
    this->body         = oselin::Floor(rect);
    this->bottom_screw = oselin::Wheel(circlebottom);
    this->top_screw    = oselin::Wheel(circletop);
    
}

//Get-Set Methods for: angle()
void   oselin::Axis::angle(float a){this->angle_ = a;}
float  oselin::Axis::angle() const{return this->angle_;}

//Get-Set Methods for: point()
void   oselin::Axis::point_x(float px){this->point_[0] = px;}
void   oselin::Axis::point_y(float py){this->point_[1] = py;}
float* oselin::Axis::point() {return this->point_;}

//TO_SVG METHOD
string oselin::Axis::svg() const{

    string str = "\n<g transform='rotate(";
    str += to_string(this->angle_) + "," + to_string(this->offset_ + this->point_[0]) + "," + to_string(this->point_[1]);
    str += ")'>";
    str += this->body.svg();
    
    str += this->bottom_screw.svg() + this->top_screw.svg();
    str += "\n</g>";
    return str;
}