#include "car_trailer.h"

#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>
#include <ostream>

using namespace std;

//Constructor
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

//Constructor - PARSING
oselin::Wheel::Wheel(string svg, float off){
    this->offset_ = off;
    this->x(stof(oselin::buffering(svg, "cx='",'\''))-this->offset_);
    this->y(stof(oselin::buffering(svg, "cy='",'\'')));
    this->radius(stof(oselin::buffering(svg, "r='",'\'')));
    this->stroke(stof(oselin::buffering(svg, "stroke-width='",'\'')));
    this->strokecolor(oselin::buffering(svg, "stroke='",'\''));
    this->color(oselin::buffering(svg, "fill='",'\''));
    //double color
    this->innercolor(oselin::buffering(svg, "fill= '",'\''));
}

//Get-Set Methods for: radius() [PUBLIC]
void   oselin::Wheel::radius(float r){this->radius_ = r;}
float  oselin::Wheel::radius() const{return this->radius_;}

//Get-Set Methods for: innercolor() [PUBLIC]
void   oselin::Wheel::innercolor(string in){this->innercolor_ = in;}
string oselin::Wheel::innercolor() const{return this->innercolor_;}

//Method: svg() [PUBLIC]
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

//Method: print() [PUBLIC]
void oselin::Wheel::print(ostream& os) const{
    this->Svg::print(os);
    os << "RADIUS: "     << this->radius_ << endl;
    os << "INNERCOLOR: " << this->innercolor_ << endl;
    os << endl;
}