#include <string>
#include <iostream>
#include <ostream>
#include <vector>

#include "car_trailer.h"
#include "Car.h"
#include"machine_car_trailer.h"

using std::string;
using std::vector;
using std::ostream;
using std::cout;
using std::endl;
using std::to_string;
using std::ostream;



//Print function
void oselin::Machine::print(ostream& os) const{
    this->Parameters::print(os);
    os <<  "n_trailers\t"       << this->n_trailers()               << endl;
}


coca_device * oselin_coca_init(oselin::Parameters *p, float newx, float newy){
    
    parametri arrayparam;
    arrayparam.inwidth  = p->car_length();
    arrayparam.inheight = p->car_height();
    arrayparam.indiam   = p->car_radius();
    arrayparam.inpx     = newx;
    arrayparam.inpy     = newy - p->car_radius();
    arrayparam.inass    = 1;

    coca_device * dev = coca_init_device(arrayparam);
    coca_try_finestrini(dev);
    coca_try_spoiler(dev);
    coca_try_tetto(dev);

    return dev;
}

//Copy function
void oselin::Machine::copyParam(oselin::Parameters p, float n_trail){
    this->Parameters::copyParam(p);
    this->n_trailers_ = n_trail;
}

//Constructor
oselin::Machine::Machine(){
    //ToDo
}

//Constructor from PARAMETERS
oselin::Machine::Machine(oselin::Parameters p, float n_trail): oselin::Parameters(p){
    
    this->n_trailers_ = n_trail;
    //If some parameters are wrong, Trailer Constructor will throw an exception
    oselin::Trailer *trailer = new oselin::Trailer(p, true, false);

    
    //After trigonometry processing, copying all parameters by using Polymorphism
    this->Parameters::copyParam(trailer);
    this->isempty(0);


    //Doing more maths
    this->svg_height(3*this->height());
    this->svg_width((this->n_trailers() +1) * this->length());
    this->offset(this->length()*0.5);
    this->y(this->y() + 2*this->car_length());


    for (int i=0; i< this->n_trailers_; i++){
        this->trailer_array_.push_back(trailer->copy());
        this->trailer_array_[i]->offset((0.5 + i) * trailer->length());
        this->trailer_array_[i]->manage_y(2*this->car_length());
    }


    float x,y;
    for (int i=0; i < this->n_floors_; i++){
        for (int j=0; j< this->n_cars_*this->n_trailers_; j++){
            int index = j/this->n_cars_;     

            y = this->y() - 1.5*this->trailer_height() - (i)*this->height() - (this->car_height()-1)/2;
            x = this->trailer_array_[index]->offset() +
                this->trailer_array_[index]->margin() + 
                (j%(int)this->n_cars_) * 
                (this->trailer_array_[index]->trailer_length() - 
                2* this->trailer_array_[index]->margin() - 
                this->car_length() );          
            
            this->car_array_.push_back(oselin_coca_init(this, x, y));   
        }
    }
}

//Copy Constructor
oselin::Machine::Machine(const oselin::Machine &m): oselin::Parameters(m){
    this->n_trailers_ = m.n_trailers();
}

//Constructor - PARSING
oselin::Machine::Machine(string svg){
    

}

//Get-Set Methods for: n_trailers()
void  oselin::Machine::n_trailers(float nv){this->n_trailers_ = nv;}
float oselin::Machine::n_trailers() const{return this->n_trailers_;}

//TO_SVG function
string oselin::Machine::svg() const{
    
    string svg = "";
    
    svg += "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n<svg xmlns='http://www.w3.org/2000/svg' width='";
    svg += to_string(this->svg_width()) + " '  height='";
    svg += to_string(this->svg_height()) + "' >";
    svg += "<rect  x='0.000000' y='0.000000' width='" + to_string(this->svg_width()) + "' height='" + to_string(this->svg_height()) + "' style='stroke-width:0.0; stroke:' fill='white' />";
    

 
    int len = this->n_trailers();
    for (int i=0; i<this->n_floors(); i++){
        for (int j=0; j < this->n_cars()*len; j++ ){
            svg += "<!--COCADEVICECAR-->\n";
            svg += coca_strg_device(this->car_array_[i*this->n_cars() * len + j],0,0);

        }
    }

    

    for (int i=0; i< len; i++) {
        svg += "<!--OSELINDEVICETRAILER-->\n";
        this->trailer_array_[i]->distributeOffset();
        svg += this->trailer_array_[i]->svg();
    }
    //mach->svg = svg;
    return svg;
    
}


