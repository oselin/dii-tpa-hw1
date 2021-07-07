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

//Copy Constructor
oselin::Svg::Svg(Svg &s){
    this->x_           = s.x();
    this->y_           = s.y();
    this->stroke_      = s.stroke();
    this->color_       = s.color();
    this->strokecolor_ = s.strokecolor();
    this->offset_      = s.offset();
}

//Get-Set Methods for: x()
void   oselin::Svg::x(float inp){this->x_ = inp;}
float  oselin::Svg::x() const{return this->x_;}

//Get-Set Methods for: y()
void   oselin::Svg::y(float inp){this->y_ = inp;}
float  oselin::Svg::y() const{return this->y_;}

//Get-Set Methods for: stroke()
void   oselin::Svg::stroke(float inp){this->stroke_ = inp;}
float  oselin::Svg::stroke() const{return this->stroke_;}

//Get-Set Methods for: color()
void   oselin::Svg::color(string inp){this->color_ = inp;}
string oselin::Svg::color() const{return this->color_;}

//Get-Set Methods for: strokecolor()
void   oselin::Svg::strokecolor(string inp){this->strokecolor_ = inp;}
string oselin::Svg::strokecolor() const{return this->strokecolor_;}

//Get-Set Methods for: offset()
void  oselin::Svg::offset(float off){this->offset_ = off;}
float oselin::Svg::offset()const{return this->offset_;}