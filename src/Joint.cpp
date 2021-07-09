#include "car_trailer.h"

#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>
#include <ostream>

using namespace std;

//Constructor
oselin::Joint::Joint(): oselin::Svg(){

}

//Copy Constructor
oselin::Joint::Joint(Joint &j): oselin::Svg(j){
    this->length_ = j.length();
    this->body = j.body;
    this->head = j.head;
}

//Constructor - PARSING
oselin::Joint::Joint(string svg, float off){
    this->offset_ = off;
    string rect = svg.substr(svg.find("<rect"),svg.find(">")-svg.find("<rect"));
    string circle = svg.substr(svg.find("<circle"),svg.find(">")-svg.find("<circle"));

    this->body = oselin::Floor(rect,    this->offset_);
    this->head = oselin::Wheel(circle,  this->offset_);
    this->head.innercolor("");

    this->x(this->body.x());
    this->y(this->body.y());
    this->length(this->body.width() + this->head.radius());
}

//Get-Set Methods for: length() [PUBLIC]
void   oselin::Joint::length(float l){this->length_ = l;}
float  oselin::Joint::length() const{return this->length_;}

//Method: svg() [PUBLIC]
string oselin::Joint::svg() const{
    string str;
    str = this->body.svg() + this->head.svg();
    return str;
}

//Method: print() [PUBLIC]
void oselin::Joint::print(ostream& os) const{
    this->Svg::print(os);
    os << "LENGTH: " << this->length_ << endl;
    os << this->body;
    os << this->head;
    os << endl;
}

//Method: dimensioning() [PUBLIC]
string oselin::Joint::dimensioning() const{
    oselin::Floor line;
    line.color("black");
    line.stroke(0);
    line.strokecolor("");
    line.offset(this->offset());

    oselin::Floor limSX = line;
    oselin::Floor limDX = line;

    line.x(this->x());
    line.y(this->y() + 1.5*this->length());
    line.width(this->length());
    line.height(4);

    limSX.x(line.x());
    limSX.y(line.y() -1.5 *this->length());
    limSX.width(1);
    limSX.height(1.8*this->length());

    limDX.x(line.x()+ this->length());
    limDX.y(line.y() -1.5 *this->length());
    limDX.width(1);
    limDX.height(1.8*this->length());

    string measure = "\n" + line.svg()
                   + "\n" + limSX.svg()
                   + "\n" + limDX.svg()
                   + oselin::textToSvg(line);

    return measure;
}