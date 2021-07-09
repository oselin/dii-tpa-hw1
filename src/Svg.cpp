#include "car_trailer.h"

#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>
#include <ostream>


using namespace std;

//Copy Constructor
oselin::Svg::Svg(Svg &s){
    this->x_           = s.x();
    this->y_           = s.y();
    this->stroke_      = s.stroke();
    this->color_       = s.color();
    this->strokecolor_ = s.strokecolor();
    this->offset_      = s.offset();
}

//Get-Set Methods for: x() [PUBLIC]
void   oselin::Svg::x(float inp){this->x_ = inp;}
float  oselin::Svg::x() const{return this->x_;}

//Get-Set Methods for: y() [PUBLIC]
void   oselin::Svg::y(float inp){this->y_ = inp;}
float  oselin::Svg::y() const{return this->y_;}

//Get-Set Methods for: stroke() [PUBLIC]
void   oselin::Svg::stroke(float inp){this->stroke_ = inp;}
float  oselin::Svg::stroke() const{return this->stroke_;}

//Get-Set Methods for: color() [PUBLIC]
void   oselin::Svg::color(string inp){this->color_ = inp;}
string oselin::Svg::color() const{return this->color_;}

//Get-Set Methods for: strokecolor() [PUBLIC]
void   oselin::Svg::strokecolor(string inp){this->strokecolor_ = inp;}
string oselin::Svg::strokecolor() const{return this->strokecolor_;}

//Get-Set Methods for: offset() [PUBLIC]
void  oselin::Svg::offset(float off){this->offset_ = off;}
float oselin::Svg::offset()const{return this->offset_;}

//Method: print() [PUBLIC]
void oselin::Svg::print(ostream& os) const{
    os << "X: "               << this->x_            << std::endl;
    os << "Y: "               << this->y_            << std::endl;
    os << "STROKE: "          << this->stroke_       << std::endl;
    os << "STROKE COLOR: "    << this->strokecolor_  << std::endl;
    os << "COLOR: "           << this->color_        << std::endl;
    os << "OFFSET: "          << this->offset_       << std::endl;
    os << std::endl;
}