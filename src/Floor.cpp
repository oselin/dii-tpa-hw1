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


oselin::Floor::Floor(): oselin::Svg(){
    this->strokecolor_ = "black";
    this->color_ = "#990000";
}

//Copy Constructor
oselin::Floor::Floor(Floor &f): oselin::Svg(f){
    this->width_ =  f.width();
    this->height_ = f.height();

}

//Get-Set Methods for: width()
void   oselin::Floor::width(float w){this->width_ = w;}
float  oselin::Floor::width() const{return this->width_;}

//Get-Set Methods for: height()
void   oselin::Floor::height(float h){this->height_ = h;}
float  oselin::Floor::height() const{return this->height_;}

//TO_SVG METHOD
string oselin::Floor::svg() const{

    cout << "VALUES" << endl;
    cout << this->offset() + this->x_ << endl;
    cout << this->offset() << endl;
    string str = "\n<rect  ";
    str += "x='" + to_string(this->offset() + this->x_) + "'";
    str += " y='" + to_string(this->y_) + "'";
    str += " width='" + to_string(this->width_) + "'";
    str += " height='" + to_string(this->height_) + "'";
    str += " style='stroke-width:" + to_string(this->stroke_) + ";";
    str += " stroke:" + this->strokecolor_ + "'";
    str += " fill='" + this->color_ + "'";
    str += " />";
    return str;
}