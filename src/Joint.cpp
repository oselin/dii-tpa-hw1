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

    this->length(this->body.width() + this->head.radius());
}

//Get-Set Methods for: length()
void   oselin::Joint::length(float l){this->length_ = l;}
float  oselin::Joint::length() const{return this->length_;}

//TO_SVG METHOD
string oselin::Joint::svg() const{
    string str;
    str = this->body.svg() + this->head.svg();
    return str;
}

//Print Method
void oselin::Joint::print(ostream& os) const{
    this->Svg::print(os);
    os << "LENGTH: " << this->length_ << endl;
    os << this->body;
    os << this->head;
    os << endl;
}