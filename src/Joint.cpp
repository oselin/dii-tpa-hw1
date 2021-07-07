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
oselin::Joint::Joint(Joint &j): oselin::Svg(j){
    this->length_ = j.length();
    this->body = j.body;
    this->head = j.head;

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