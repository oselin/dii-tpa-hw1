
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



//Get-Set Methods for: x()
void   oselin::Trailer::x(float inp){this->parameters_.x_ = inp;}
float  oselin::Trailer::x() const{return this->parameters_.x_;}

//Get-Set Methods for: y()
void   oselin::Trailer::y(float inp){this->parameters_.y_ = inp;}
float  oselin::Trailer::y() const{return this->parameters_.y_;}

//Get-Set Methods for: length()
void   oselin::Trailer::length(float l){this->parameters_.length_ = l;}
float  oselin::Trailer::length() const{return this->parameters_.length_;}

//Get-Set Methods for: height()
void   oselin::Trailer::height(float h){this->parameters_.height_ = h;}
float  oselin::Trailer::height() const{return this->parameters_.height_;}

//Get-Set Methods for: offset()
void   oselin::Trailer::offset(float off){this->parameters_.offset_ = off;}
float  oselin::Trailer::offset() const{return this->parameters_.offset_;}

//Get-Set Methods for: parameters()
void  oselin::Trailer::parameters(oselin::Parameters p){this->parameters_ = p;}
oselin::Parameters oselin::Trailer::parameters() const{return this->parameters_;}

//Get-Set Methods for: svg_width()
void  oselin::Trailer::svg_width(float nv){this->parameters_.svg_width_ = nv;}
float oselin::Trailer::svg_width() const{return this->parameters_.svg_width_;} 

//Get-Set Methods for: svg_height()
void  oselin::Trailer::svg_height(float nv){this->parameters_.svg_height_ = nv;}
float oselin::Trailer::svg_height() const{return this->parameters_.svg_height_;}

//Get-Set Methods for: trailer_length()
void  oselin::Trailer::trailer_length(float nv){this->parameters_.trailer_length_ = nv;}
float oselin::Trailer::trailer_length() const{return this->parameters_.trailer_length_;}

//Get-Set Methods for: trailer_height()
void  oselin::Trailer::trailer_height(float nv){this->parameters_.trailer_height_ = nv;}
float oselin::Trailer::trailer_height() const{return this->parameters_.trailer_height_;}

//Get-Set Methods for: car_length()
void  oselin::Trailer::car_length(float nv){this->parameters_.car_length_ = nv;}
float oselin::Trailer::car_length() const{return this->parameters_.car_length_;}

//Get-Set Methods for: car_height()
void  oselin::Trailer::car_height(float nv){this->parameters_.car_height_ = nv;}
float oselin::Trailer::car_height() const{return this->parameters_.car_height_;}

//Get-Set Methods for: car_radius()
void  oselin::Trailer::car_radius(float nv){this->parameters_.car_radius_ = nv;}
float oselin::Trailer::car_radius() const{return this->parameters_.car_radius_;}

//Get-Set Methods for: n_cars()
void  oselin::Trailer::n_cars(float nv){this->parameters_.n_cars_ = nv;}
float oselin::Trailer::n_cars() const{return this->parameters_.n_cars_;}

//Get-Set Methods for: n_floors()
void  oselin::Trailer::n_floors(float nv){this->parameters_.n_floors_ = nv;}
float oselin::Trailer::n_floors() const{return this->parameters_.n_floors_;}

void oselin::Trailer::copy(){
    this->downfloor.offset(this->offset());
    this->upfloor.offset(this->offset());
    this->front_wheel.offset(this->offset());
    this->rear_wheel.offset(this->offset());
    this->rear_joint.offset(this->offset());
    this->front_joint.offset(this->offset());
    this->rear_axis.offset(this->offset());
    this->front_axis.offset(this->offset());
    this->rear_joint.body.offset(this->offset());
    this->rear_joint.head.offset(this->offset());
    this->front_joint.body.offset(this->offset());
    this->front_joint.head.offset(this->offset());
    this->front_axis.body.offset(this->offset());
    this->front_axis.bottom_screw.offset(this->offset());
    this->front_axis.top_screw.offset(this->offset());
    this->rear_axis.body.offset(this->offset());
    this->rear_axis.bottom_screw.offset(this->offset());
    this->rear_axis.top_screw.offset(this->offset());
    
}



//TRIGONOMETRY SUPPORTING FUNCTIONS
oselin::Floor trigonometry_floors(oselin::Trailer *trailer, int mode){
    if (trailer!=NULL){

        oselin::Floor f;
        
        f.width(trailer->trailer_length());
        f.height(trailer->trailer_length()/15);

        trailer->trailer_height(f.height());

        f.stroke(f.height()/20);
        f.x(0);
        f.y(trailer->svg_height() - (trailer->svg_height() - trailer->height())/2 - mode*trailer->height());

        return f;
    }
    throw logic_error("Pointer is null.");
   

}

oselin::Wheel trigonometry_wheel(oselin::Trailer *trailer, int mode){
    if (trailer!=NULL){

        oselin::Wheel wheel;

        float wheeloffset = trailer->trailer_length()/12;

        wheel.radius(trailer->downfloor.height() / 40 * 2 * trailer->car_radius());
        wheel.stroke(wheel.radius()/10);
        wheel.x(trailer->downfloor.x() + pow(-1,mode)* wheeloffset + mode*trailer->trailer_length());
        wheel.y(trailer->downfloor.y() + trailer->downfloor.height() - wheel.radius()/4);
        return wheel;
    }
    throw logic_error("Pointer is null");
}

oselin::Joint trigonometry_joint(oselin::Trailer *trailer, int mode){

    if (trailer != NULL){
        oselin::Joint j;
        
        j.body.width(DOWNOFFSET);
        j.body.height(DOWNOFFSET/5);
        j.body.x(trailer->downfloor.x() + (mode-1)*DOWNOFFSET + mode*trailer->trailer_length());
        j.body.y(trailer->downfloor.y() + trailer->downfloor.height()/2 - j.body.height()/2);
        j.body.stroke(j.body.height()/20);
        
        j.head.x(j.body.x() + mode*j.body.width());
        j.head.y(j.body.y() + j.body.height()/2);
        j.head.radius(trailer->car_radius()/3);
        j.head.stroke(trailer->car_radius()/10);
        j.head.innercolor("");
        j.head.color("white");

        j.length(j.body.width() + j.head.radius());

        return j;
    }
    throw logic_error("Pointer is null");
}

oselin::Axis trigonometry_axis(oselin::Trailer *trailer, int mode){

    if (trailer != NULL){
        oselin::Axis a; 

        a.body.x(trailer->trailer_length()*(mode+1)/3 + trailer->upfloor.x());
        a.body.y(trailer->upfloor.y());
        a.body.height(trailer->height() + trailer->downfloor.height());
        a.body.width(trailer->height()/10);
        a.body.stroke(a.body.width()/20);
        
        a.top_screw.innercolor("");
        a.top_screw.color("white");
        a.top_screw.radius(a.body.width() /3);
        a.top_screw.stroke((trailer->downfloor.height() / 40 * 2 * trailer->car_radius())/10);
        a.top_screw.x(a.body.width()/2 + a.body.x());
        a.top_screw.y(a.body.width()/2 + a.body.y());
        
        
        a.bottom_screw.innercolor("");
        a.bottom_screw.color("white");
        a.bottom_screw.radius(a.body.width() /3);
        a.bottom_screw.stroke((trailer->downfloor.height() / 40 * 2 * trailer->car_radius())/10);
        a.bottom_screw.x(a.body.width()/2 + a.body.x());
        a.bottom_screw.y(-a.body.width()/2 + a.body.y() + a.body.height());
        a.point_x(a.body.x() + a.body.width()/2);
        a.point_y(a.body.y() + a.body.height()/2);
              
        return a;
    }
    throw logic_error("Pointer is null");
}

int oselin::trigonometry(oselin::Trailer *trailer, bool automaticoffset){

    if (trailer == NULL) throw logic_error("Pointer is null");

    trailer->downfloor =   trigonometry_floors(trailer, DOWN);
    trailer->rear_wheel =  trigonometry_wheel (trailer, REAR);
    trailer->front_wheel = trigonometry_wheel (trailer, FRONT);
    trailer->rear_joint =  trigonometry_joint (trailer, REAR);
    trailer->front_joint = trigonometry_joint (trailer, FRONT);
    
    if (trailer->n_floors() > 1){
        trailer->upfloor =    trigonometry_floors(trailer, (int)UP);
        trailer->rear_axis =  trigonometry_axis  (trailer, REAR);
        trailer->front_axis = trigonometry_axis  (trailer, FRONT);
    }

    trailer->x(trailer->rear_joint.head.x());
    trailer->y(trailer->rear_joint.head.y());
    trailer->length(trailer->trailer_length()+ 2*trailer->rear_joint.length() - 2* trailer->rear_joint.head.radius());
    
    if (automaticoffset){
        trailer->offset((trailer->svg_width() - trailer->downfloor.width())/2);
    }
    return 0;
}

string measures(){
    string measure;
    for (int i=0; i<6; i++){
        measure += " ";
    }

    return measure;
}


/**
 * @param element to measure
 * @param main_dimension
 * */
string get_measures(){
    string measures;

    oselin::Floor line;
    oselin::Floor SXlim;
    oselin::Floor DXlim;


    
    return measures;
}



//TO_SVG METHOD
string oselin::Trailer::svg(bool with_header, bool with_measures) const{
       
    string svg;
    //if (device!=NULL){// CHOOSE HOW TO TEST IF IT EXISTS
        if (with_header){

            svg = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n<svg xmlns='http://www.w3.org/2000/svg' width='";
            svg += to_string(this->svg_width()) + " '  height='";
            svg += to_string(this->svg_height()) + "' >";

            svg += "<rect  x='0.000000' y='0.000000' width='" + to_string(this->svg_width()) + "' height='" + to_string(this->svg_height()) + "' style='stroke-width:0.0; stroke:' fill='white' />";
        }
        svg += "\n<!--#1-->";
        svg += "\n" + this->rear_joint.svg();
        svg += "\n<!--#2-->";
        svg += "\n" +this->front_joint.svg();
        svg += "\n<!--#3-->";
        svg += "\n" + this->downfloor.svg();
        svg += "\n<!--#4-->";
        svg += "\n" + this->front_wheel.svg();
        svg += "\n<!--#5-->";
        svg += "\n" + this->rear_wheel.svg();
        
        if (this->n_floors() > 1) {
            svg += "\n<!--#6-->";
            svg += "\n" + this->upfloor.svg();
            svg += "\n<!--#7-->";
            svg += "\n" + this->rear_axis.svg();
            svg += "\n<!--#8-->";
            svg += "\n" + this->front_axis.svg();
        }
        
        if (with_measures) svg += measures();

        
    return svg;
}

//Copy Constructor by reference
oselin::Trailer::Trailer(Trailer &t){
    cout << "Reference constructor has been invoked" << endl;
    this->parameters_.svg_width_ =  t.svg_width();
    this->parameters_.svg_height_ = t.svg_height();
    this->parameters_.length_ =     t.length();
    this->parameters_.x_ =          t.x();
    this->parameters_.y_ =          t.y();
    this->parameters_.offset_ =     t.offset();
    this->downfloor =               t.downfloor;
    this->upfloor =                 t.upfloor;
    this->front_wheel =             t.front_wheel;
    this->rear_wheel =              t.rear_wheel;
    this->rear_joint =              t.rear_joint;
    this->front_joint =             t.front_joint;
    this->rear_axis =               t.rear_axis;
    this->front_axis =              t.front_axis;
    this->parameters_ =             t.parameters();

    this->copy();
}

//Copy Constructor by address
oselin::Trailer::Trailer(Trailer *t){
    cout << "Pointer constructor has been invoked" << endl;
    this->parameters_.svg_width_ =  t->svg_width();
    this->parameters_.svg_height_ = t->svg_height();
    this->parameters_.length_ =     t->length();
    this->parameters_.x_ =          t->x();
    this->parameters_.y_ =          t->y();
    this->parameters_.offset_ =     t->offset();
    this->downfloor =   t->downfloor;
    this->upfloor =     t->upfloor;
    this->front_wheel = t->front_wheel;
    this->rear_wheel =  t->rear_wheel;
    this->rear_joint =  t->rear_joint;
    this->front_joint = t->front_joint;
    this->rear_axis =   t->rear_axis;
    this->front_axis =  t->front_axis;
    this->parameters_ = t->parameters();

    this->copy();
}

//Constructor - PARAMETERS
oselin::Trailer::Trailer(oselin::Parameters parameters, bool avoid_svg){
    cout << "Constructor has been invoked" << endl;
 
    if (parameters.car_radius_ < 16 || parameters.car_radius_ > 18){
        throw std::out_of_range("Radius value is wrong!");
    }

    //Estimating the required margin values
    parameters.margin_ = parameters.car_length_/2;
    
    //Redefining length and height
    parameters.trailer_length_ = parameters.car_length_ * parameters.n_cars_  + (parameters.n_cars_+3)*parameters.car_length_/2;
    parameters.height_ = parameters.car_height_ * parameters.n_floors_ + 100;
    
    //CONSTRAINTS
    if (!avoid_svg){
        if (parameters.svg_width_ < parameters.trailer_length_){
            throw std::invalid_argument("INIT: WIDTH ERROR");
        }
        if (parameters.svg_height_ < parameters.trailer_height_*5/4){
            throw std::invalid_argument("INIT: HEIGHT ERROR");
        }
    }
    if (parameters.n_cars_ == 1 && parameters.n_floors_ == 2){
        throw std::invalid_argument("INIT: STRUCTURAL ERROR");
    }
    if (parameters.car_length_ < (parameters.car_height_*4/5)){
        throw std::invalid_argument("INIT: CAR DIMENSIONS ERROR");
    }
    if (parameters.n_cars_ > 2){
        throw std::out_of_range("Too many cars!");
    }
    if (parameters.n_floors_ > 2){
        throw std::out_of_range("Too many floors!");
    }

    
    this->parameters_ = parameters;


    cout << "PARAMETERS: " << endl;
    cout << "MARGIN " << this->parameters_.margin_ << endl;
    cout << "TRAILER LENGTH " << this->parameters_.trailer_length_ << endl;
    cout << "TRAILER HEIGHT " << this->parameters_.trailer_height_ << endl;    
    cout << "SVG LENGTH " << this->parameters_.svg_width_ << endl;
    cout << "SVG HEIGHT " << this->parameters_.svg_height_ << endl; 

    oselin::trigonometry(this);
    this->copy();
}

//Constructor - PARSING
oselin::Trailer::Trailer(string s){}




