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

//Get-Set Methods for: width() [PUBLIC]
void   oselin::Floor::width(float w){this->width_ = w;}
float  oselin::Floor::width() const{return this->width_;}

//Get-Set Methods for: height() [PUBLIC]
void   oselin::Floor::height(float h){this->height_ = h;}
float  oselin::Floor::height() const{return this->height_;}

//Method: svg() [PUBLIC]
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

//Method: print() [PUBLIC]
void oselin::Floor::print(ostream& os) const{
    this->Svg::print(os);
    os << "WIDTH: "  << this->width_ << endl;
    os << "HEIGHT: " << this->height_ << endl;
    os << endl;
}

//Method: dimensioning() [PUBLIC]
string oselin::Floor::dimensioning() const{
    
    oselin::Floor line;
    line.color("black");
    line.stroke(0);
    line.strokecolor("");
    line.offset(this->offset());

    oselin::Floor limSX = line;
    oselin::Floor limDX = line;

    line.x(this->x());
    line.y(this->y() - 1.5*this->height());
    line.width(this->width());
    line.height(4);
    
    limSX.x(line.x());
    limSX.y(line.y()*0.95);
    limSX.width(1);
    limSX.height(3*this->height());

    limDX.x(line.x() + this->width());
    limDX.y(line.y()*0.95);
    limDX.width(1);
    limDX.height(3*this->height());

    string measure = "\n" + line.svg()
            + "\n" + limSX.svg()
            + "\n" + limDX.svg()
            + oselin::textToSvg(line);

    line.x(this->x()-2*this->height());
    line.y(this->y());
    line.width(4);
    line.height(this->height());

    limSX.x(line.x() - 0.2*this->height());
    limSX.y(line.y());
    limSX.width(2.5*this->height());
    limSX.height(1);

    limDX.x(line.x() - 0.2*this->height());
    limDX.y(line.y() + this->height());
    limDX.width(2.5*this->height());
    limDX.height(1);

    measure += "\n" + line.svg()
            + "\n" + limSX.svg()
            + "\n" + limDX.svg()
            + oselin::textToSvg(line);





    return measure;

}