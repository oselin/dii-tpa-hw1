#include "car_trailer.h"

#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>
#include <ostream>

using namespace std;

//Constructor
oselin::Floor::Floor(): oselin::Svg(){
    this->strokecolor_ = "black";
    this->color_ = "#990000";
}

//Copy Constructor
oselin::Floor::Floor(Floor &f): oselin::Svg(f){
    this->width_ =  f.width();
    this->height_ = f.height();

}

//Constructor - PARSING
oselin::Floor::Floor(string svg, float off){
    if (svg != ""){
        this->offset_ = off;
        this->x(stof(oselin::buffering(svg, "x='",'\''))-this->offset());
        this->y(stof(oselin::buffering(svg, "y='",'\'')));
        this->width(stof(oselin::buffering(svg, "width='",'\'')));
        this->height(stof(oselin::buffering(svg, "height='",'\'')));
        this->color(oselin::buffering(svg, "fill='",'\''));
        this->stroke(stof(oselin::buffering(svg, "stroke-width:",';')));
        this->strokecolor(oselin::buffering(svg, "stroke:", '\''));
    }
    else throw range_error("FLOOR: String is empty.");
}

//Get-Set Methods for: width()
void   oselin::Floor::width(float w){this->width_ = w;}
float  oselin::Floor::width() const{return this->width_;}

//Get-Set Methods for: height()
void   oselin::Floor::height(float h){this->height_ = h;}
float  oselin::Floor::height() const{return this->height_;}

//TO_SVG METHOD
string oselin::Floor::svg() const{

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

//Print Method
void oselin::Floor::print(ostream& os) const{
    this->Svg::print(os);
    os << "WIDTH: "  << this->width_ << endl;
    os << "HEIGHT: " << this->height_ << endl;
    os << endl;
}

