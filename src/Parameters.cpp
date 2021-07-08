#include "car_trailer.h"

#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>
#include <ostream>

using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::stof;
using std::ostream;


//Print function
void oselin::Parameters::print(ostream& os) const{
    os <<  "isempty\t\t"      << this->isempty()              << endl;
    os <<  "x\t\t"            << this->x()                    << endl;
    os <<  "y\t\t"            << this->y()                    << endl;
    os <<  "length\t\t"       << this->length()               << endl;
    os <<  "height\t\t"       << this->height()               << endl;
    os <<  "offset\t\t"       << this->offset()               << endl;
    os <<  "svg_width\t"      << this->svg_width()            << endl;  
    os <<  "svg_height\t"     << this->svg_height()           << endl;
    os <<  "trailer_length\t" << this->trailer_length()       << endl;
    os <<  "trailer_height\t" << this->trailer_height()       << endl;    
    os <<  "car_length\t"     << this->car_length()           << endl;
    os <<  "car_height\t"     << this->car_height()           << endl;
    os <<  "car_radius\t"     << this->car_radius()           << endl;
    os <<  "n_cars\t\t"       << this->n_cars()               << endl;
    os <<  "n_floors\t"       << this->n_floors()             << endl;
    os <<  "margin\t\t"       << this->margin()               << endl;
    os << endl;
}

//Copy function by reference
void oselin::Parameters::copyParam(const oselin::Parameters &p){

    this->isempty_          = p.isempty();      
    this->x_                = p.x();
    this->y_                = p.y();
    this->length_           = p.length();
    this->height_           = p.height();
    this->offset_           = p.offset();
    this->svg_width_        = p.svg_width();
    this->svg_height_       = p.svg_height();
    this->trailer_length_   = p.trailer_length();
    this->trailer_height_   = p.trailer_height();
    this->car_length_       = p.car_length();
    this->car_height_       = p.car_height();
    this->car_radius_       = p.car_radius();
    this->n_cars_           = p.n_cars();
    this->n_floors_         = p.n_floors();
    this->margin_           = p.margin();
    
}

//Copy function by address
void oselin::Parameters::copyParam(oselin::Parameters *p){
    this->isempty_          = p->isempty();      
    this->x_                = p->x();
    this->y_                = p->y();
    this->length_           = p->length();
    this->height_           = p->height();
    this->offset_           = p->offset();
    this->svg_width_        = p->svg_width();
    this->svg_height_       = p->svg_height();
    this->trailer_length_   = p->trailer_length();
    this->trailer_height_   = p->trailer_height();
    this->car_length_       = p->car_length();
    this->car_height_       = p->car_height();
    this->car_radius_       = p->car_radius();
    this->n_cars_           = p->n_cars();
    this->n_floors_         = p->n_floors();
    this->margin_           = p->margin();
}

//Constructor
oselin::Parameters::Parameters(){
    //Default constructor
}
//Constructor from cli-input
oselin::Parameters::Parameters(char * argv[]){
    if (argv != NULL){
        oselin::Parameters param;
        try{
            this->svg_width_  = stof(argv[2]);
            this->svg_height_ = stof(argv[3]);
            this->car_length_ = stof(argv[4]);
            this->car_height_ = stof(argv[5]);
            this->car_radius_ = stof(argv[6]);
            this->n_cars_     = stof(argv[7]);
            this->n_floors_   = stof(argv[8]);
        }catch (const std::exception &e){throw e;}
        this->isempty_ = 0;
    }
    else throw std::invalid_argument("Something went wrong.");
}

//Copy Constructor by Reference
oselin::Parameters::Parameters(const oselin::Parameters &p){
    this->copyParam(p);
}

//Copy Constructor by Address
oselin::Parameters::Parameters(oselin::Parameters *p){
    this->copyParam(p);
}

//Get-Set Methods for: isempty()
void   oselin::Parameters::isempty(bool inp){this->isempty_ = inp;}
bool   oselin::Parameters::isempty() const{return this->isempty_ ;}

//Get-Set Methods for: x()
void   oselin::Parameters::x(float inp){this->x_ = inp;}
float  oselin::Parameters::x() const{return this->x_;}

//Get-Set Methods for: y()
void   oselin::Parameters::y(float inp){this->y_ = inp;}
float  oselin::Parameters::y() const{return this->y_;}

//Get-Set Methods for: length()
void   oselin::Parameters::length(float l){this->length_ = l;}
float  oselin::Parameters::length() const{return this->length_;}

//Get-Set Methods for: height()
void   oselin::Parameters::height(float h){this->height_ = h;}
float  oselin::Parameters::height() const{return this->height_;}

//Get-Set Methods for: offset()
void   oselin::Parameters::offset(float off){this->offset_ = off;}
float  oselin::Parameters::offset() const{return this->offset_;}

//Get-Set Methods for: svg_width()
void  oselin::Parameters::svg_width(float nv){this->svg_width_ = nv;}
float oselin::Parameters::svg_width() const{return this->svg_width_;} 

//Get-Set Methods for: svg_height()
void  oselin::Parameters::svg_height(float nv){this->svg_height_ = nv;}
float oselin::Parameters::svg_height() const{return this->svg_height_;}

//Get-Set Methods for: trailer_length()
void  oselin::Parameters::trailer_length(float nv){this->trailer_length_ = nv;}
float oselin::Parameters::trailer_length() const{return this->trailer_length_;}

//Get-Set Methods for: trailer_height()
void  oselin::Parameters::trailer_height(float nv){this->trailer_height_ = nv;}
float oselin::Parameters::trailer_height() const{return this->trailer_height_;}

//Get-Set Methods for: car_length()
void  oselin::Parameters::car_length(float nv){this->car_length_ = nv;}
float oselin::Parameters::car_length() const{return this->car_length_;}

//Get-Set Methods for: car_height()
void  oselin::Parameters::car_height(float nv){this->car_height_ = nv;}
float oselin::Parameters::car_height() const{return this->car_height_;}

//Get-Set Methods for: car_radius()
void  oselin::Parameters::car_radius(float nv){this->car_radius_ = nv;}
float oselin::Parameters::car_radius() const{return this->car_radius_;}

//Get-Set Methods for: n_cars()
void  oselin::Parameters::n_cars(float nv){this->n_cars_ = nv;}
float oselin::Parameters::n_cars() const{return this->n_cars_;}

//Get-Set Methods for: n_floors()
void  oselin::Parameters::n_floors(float nv){this->n_floors_ = nv;}
float oselin::Parameters::n_floors() const{return this->n_floors_;}

//Get-Set Methods for: svg_height()
void  oselin::Parameters::margin(float m){this->margin_ = m;}
float oselin::Parameters::margin() const{return this->margin_;}
