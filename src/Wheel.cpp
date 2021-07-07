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


oselin::Wheel::Wheel(): oselin::Svg(){
    this->strokecolor_ = "black";
    this->color_  = "black";
    this->innercolor_ = "gray";
}

//Copy Constructor
oselin::Wheel::Wheel(Wheel &w): oselin::Svg(w){
    this->radius_ =     w.radius();
    this->innercolor_ = w.innercolor();

}

//Get-Set Methods for: radius()
void   oselin::Wheel::radius(float r){this->radius_ = r;}
float  oselin::Wheel::radius() const{return this->radius_;}

//Get-Set Methods for: innercolor()
void   oselin::Wheel::innercolor(string in){this->innercolor_ = in;}
string oselin::Wheel::innercolor() const{return this->innercolor_;}


//TO_SVG METHOD
string oselin::Wheel::svg() const{
    string str;
    str += "\n<circle";
    str += " cx='" + to_string(this->offset_ + this->x_) + "'";
    str += " cy='" + to_string(this->y_) + "'";
    str += " r='" + to_string(this->radius_) + "'";
    str += " stroke='" + this->strokecolor_ + "'";
    str += " stroke-width='" + to_string(this->stroke_) + "'";
    str += " fill='" + this->color_ + "'";
    str += " />";

    if (this->innercolor_ != ""){
        str += "\n<circle";
        str += " cx='" + to_string(this->offset_ + this->x_) + "'";
        str += " cy='" + to_string(this->y_) + "'";
        str += " r='" + to_string(this->radius_*3/4) + "'";
        str += " stroke='" + this->strokecolor_ + "'";
        str += " stroke-width='" + to_string(this->stroke_) + "'";
        str += " fill= '" + this->innercolor_ + "'";
        str += " />";   
    }
    return str;
}