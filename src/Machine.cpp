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



//Print function [PUBLIC]
void oselin::Machine::print(ostream& os) const{
    this->Parameters::print(os);
    os <<  "n_trailers\t"       << this->n_trailers()               << endl;
}

//Get-Set Methods for: n_trailers() [PUBLIC]
void  oselin::Machine::n_trailers(float nv){this->n_trailers_ = nv;}
float oselin::Machine::n_trailers() const{return this->n_trailers_;}

//Get-Set Methods for: trailer_array() [PUBLIC]
void oselin::Machine::trailer_array(vector<oselin::Trailer *> ta){this->trailer_array_ = ta;}
vector<oselin::Trailer *> oselin::Machine::trailer_array() const {return this->trailer_array_;}               

//Get-Set Methods for: car_array() [PUBLIC]
void oselin::Machine::car_array(vector<coca_device*> ca){this->car_array_ = ca;}
vector<coca_device*> oselin::Machine::car_array() const {return this->car_array_;}   

//Copy function [PUBLIC]
void oselin::Machine::copyParam(oselin::Parameters p, float n_trail){
    this->Parameters::copyParam(p);
    this->n_trailers_ = n_trail;
}

//Function to adapt COCA library to this project
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

//Method: create() [PRIVATE]
void oselin::Machine::create(oselin::Parameters p, float n_trail){
    
    this->n_trailers_ = n_trail;
    
    //If some parameters are wrong, Trailer Constructor will throw an exception
    oselin::Trailer *trailer = new oselin::Trailer(p, true);

    trailer->svg_height(3*trailer->height());
    oselin::trigonometry(trailer, false);
    
    //After trigonometry processing, copying all parameters by using Polymorphism
    this->Parameters::copyParam(trailer);
    this->isempty(0);


    //Doing more maths
    this->svg_height(3*this->height());
    this->svg_width((this->n_trailers() +1) * this->length());
    this->offset(this->length()*0.5);
    
    for (int i=0; i< this->n_trailers_; i++){
        this->trailer_array_.push_back(trailer->copy());
        this->trailer_array_[i]->offset((0.5 + i) * trailer->length());
        this->trailer_array_[i]->isempty(false);
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

//Method: svg() [PUBLIC]
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
    return svg;
    
}

//Constructor
oselin::Machine::Machine(){
}

//Constructor from PARAMETERS
oselin::Machine::Machine(oselin::Parameters p, float n_trail): oselin::Parameters(p){
    this->create(p,n_trail);
}

//Constructor from PARAMETERS
oselin::Machine::Machine(oselin::Parameters *p, float n_trail): oselin::Parameters(p){
    this->create(*p,n_trail);
}

//Copy Constructor
oselin::Machine::Machine(const oselin::Machine &m): oselin::Parameters(m){
    this->n_trailers_ =    m.n_trailers();
    this->trailer_array_ = m.trailer_array();
    this->car_array_ =     m.car_array();
}

//Copy Constructor - by address
oselin::Machine::Machine(oselin::Machine *m): oselin::Parameters(m){
    this->n_trailers_ =    m->n_trailers();
    this->trailer_array_ = m->trailer_array();
    this->car_array_ =     m->car_array();
}

//Constructor - PARSING
oselin::Machine::Machine(string svg){
    if (svg!=""){

        
        //Count number of trailers and cars
        int check = svg.find("<!--OSELINDEVICETRAILER-->",1);
        int counter[] = {0,0};

        while (check>0){
            check = svg.find("<!--OSELINDEVICETRAILER-->", check+30);
            counter[0]++;
            
        }

        check = svg.find("<!--COCADEVICECAR-->",1);
        while (check< svg.length()){
            check = svg.find("<!--COCADEVICECAR-->", check+30);
            counter[1]++;
        }
        
        
        if (counter[1]/counter[0] < 3) {
            this->n_cars(counter[1]/counter[0]);
            this->n_floors(1);
        }
        else{
            this->n_cars(counter[1]/counter[0]/2);
            this->n_floors(2);
        }


        int pos = svg.find("<!--OSELINDEVICETRAILER-->", 0);
        int len = svg.find("<!--OSELINDEVICETRAILER-->", pos+30) - pos;


        oselin::Trailer trailer(svg.substr(pos,len), 1);
  
        //Creation
        this->create(trailer, counter[0]);

        }
        else throw std::logic_error("String is empty.");
    }

//Deconstructor
oselin::Machine::~Machine(){
    for (int i=this->trailer_array_.size()-1; i>=0; i--){
        delete this->trailer_array_[i];
        this->trailer_array_.pop_back();

    }

    for (int j=this->car_array_.size()-1; j>=0; j--){
        delete this->trailer_array_[j];
        this->car_array_.pop_back();

    }
}