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


//Copy COnstructor
oselin::Axis::Axis(Axis &a): oselin::Svg(a){
    this->body =         a.body;
    this->bottom_screw = a.bottom_screw;
    this->top_screw =    a.top_screw;
    this->angle_ =       a.angle();
    this->point_[0]=     a.point()[0];
    this->point_[1]=     a.point()[1];
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