
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
        
        if (with_measures) svg += oselin::measures();

        
    return svg;
}

//Constructor - PARSING
oselin::Trailer::Trailer(string svg){
    if (svg != ""){
        int pieces[7][2];
        for (int i=1;i<9;i++){
            int index = svg.find(oselin::checkpoint(i));
            int len = svg.find(oselin::checkpoint(i+1)) - index;
            pieces[i-1][0] = index+11;
            pieces[i-1][1] = len-11;
        }
        this->svg_width  (stof(oselin::buffering(svg.substr(0,pieces[0][0]),"width='", '\'')));
        this->svg_height (stof(oselin::buffering(svg.substr(0,pieces[0][0]),"height='",'\'')));
       
        this->rear_joint      = oselin::Joint(svg.substr(pieces[0][0], pieces[0][1]));
        this->front_joint     = oselin::Joint(svg.substr(pieces[1][0], pieces[1][1]));
        this->downfloor       = oselin::Floor(svg.substr(pieces[2][0], pieces[2][1]));
        this->front_wheel     = oselin::Wheel(svg.substr(pieces[3][0], pieces[3][1]));//double color
        this->rear_wheel      = oselin::Wheel(svg.substr(pieces[4][0], pieces[4][1])); //double color

        if (pieces[5][1] > 0){
            this->upfloor    = oselin::Floor(svg.substr(pieces[5][0], pieces[5][1]));
            this->rear_axis  = oselin::Axis (svg.substr(pieces[6][0], pieces[6][1]));
            this->front_axis = oselin::Axis (svg.substr(pieces[7][0], pieces[7][1]));
            this->n_floors(2);
        }
        else this->n_floors(1);

        //this->length( = device->downfloor.width;
        //this->height( = (float)(device->downfloor.y - device->upfloor.y  - 100) /device->param.nfloors;
        //this->n_cars( = (int)(device->param.length/4.5);
        Parameters p;
        //p.length = (float)(device->param.length/4.5);
        //p.height = device->param.height;
        this->car_radius(20 * this->rear_wheel.radius()/this->downfloor.height());
        
        
        //if (p.nfloors > 1)  p.ncars = 2;
        //else  p.ncars = 2; //IMPOSSIBLE TO UNDERSTAND IF TRAILER IS MADE FOR ONE LONG CAR INSTEAD OF TWO SHORT ONES
        //if (!svgoverride){
        //    p.svgwidth  = device->param.svgwidth ;  
        //    p.svgheight = device->param.svgheight;
        //}

        oselin::trigonometry(this);
        this->copy();
    }
    throw std::range_error("File is empty!");
}

