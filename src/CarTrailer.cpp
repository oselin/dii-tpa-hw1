
#include "car_trailer.h"
#include <iostream>
#include <string>
#include <cmath>

#include <stdexcept>


using namespace std;


//TRIGONOMETRY SUPPORTING FUNCTIONS
oselin::Floor * trigonometry_floors(oselin::Trailer trailer,  string m){
    if (trailer!=NULL){
        oselin::Floor *f; int mode;
        if (m == "down") mode = 0;
        else mode = 1;
        
        f->width(trailer.trailer_length());
        f->height(trailer.trailer_length()/15);
        f->stroke(f->height()/20);
        f->x(0);
        f->y(trailer.svg_height() - (trailer.svg_height() - trailer.trailer_height())/2 - mode*trailer.trailer_height();
        return f;
    }
    throw logic_error("Pointer is null.");
   

}

oselin::Wheel * trigonometry_wheel(oselin::Trailer trailer, string m){
    if (trailer!=NULL){
        int mode;
        oselin::Wheel *wheel;
        if (m=="rear") mode = 0;
        else mode = 1;
        float wheeloffset = dev->param.length/12;

        wheel->radius = dev->downfloor.height / 40 * 2 * dev->param.radius;
        wheel->stroke = wheel->radius/10;
        wheel->x = dev->downfloor.x + pow(-1,mode)* wheeloffset + mode*dev->param.length;
        wheel->y = dev->downfloor.y + dev->downfloor.height - wheel->radius/4;

        return 0;
    }else return 1;
}

int trigjoint(OselinDevice *dev, string m){
    if (dev!=NULL){
        Oselin_Joint *joint; int mode;
        if (m =="rear"){
            mode = 0;
            joint = &dev->rearjoint;
        }
        else{
            mode = 1;
            joint = &dev->frontjoint;
        }
        
        joint->body.width = DOWNOFFSET;
        joint->body.height = DOWNOFFSET/5;
        joint->body.x = dev->downfloor.x + (mode-1)*DOWNOFFSET + mode*dev->param.length;
        joint->body.y = dev->downfloor.y+ dev->downfloor.height/2 - joint->body.height/2;
        joint->body.stroke = joint->body.height/20;
        
        joint->head.x = joint->body.x + mode*joint->body.width;
        joint->head.y = joint->body.y + joint->body.height/2;
        joint->head.radius = dev->param.radius/3;
        joint->head.stroke =  dev->param.radius/10;
        joint->head.innercolor = "";
        joint->head.outercolor = "white";

        joint->length = joint->body.width + joint->head.radius;
        return 0;
    }else return 1;
}

int trigaxis(OselinDevice *dev, string m){
    if (dev!=NULL){
        Oselin_Axis *axis; int mode;
        if (m =="rear"){
            mode = 0;
            axis = &dev->rearaxis;
        }
        else{
            mode = 1;
            axis = &dev->frontaxis;
        }

        axis->body.x = dev->param.length*(mode+1)/3 + dev->upfloor.x;
        axis->body.y = dev->upfloor.y;
        axis->body.height = dev->param.height + dev->downfloor.height;
        axis->body.width = dev->param.height/10;
        axis->body.stroke = axis->body.width/20;
        
        axis->topscrew.innercolor = "";
        axis->topscrew.outercolor = "white";
        axis->topscrew.radius = axis->body.width /3;
        axis->topscrew.stroke = (dev->downfloor.height / 40 * 2 * dev->param.radius)/10;
        axis->topscrew.x = axis->body.width/2 + axis->body.x;
        axis->topscrew.y = axis->body.width/2 + axis->body.y;
        
        
        axis->bottomscrew.innercolor = "";
        axis->bottomscrew.outercolor = "white";
        axis->bottomscrew.radius = axis->body.width /3;
        axis->bottomscrew.stroke = (dev->downfloor.height / 40 * 2 * dev->param.radius)/10;
        axis->bottomscrew.x = axis->body.width/2 + axis->body.x;
        axis->bottomscrew.y = -axis->body.width/2 + axis->body.y + axis->body.height;
        axis->rotationpoint[0] = axis->body.x + axis->body.width/2;
        axis->rotationpoint[1] = axis->body.y + axis->body.height/2;
        return 0;
    }else return 1;
     
}

/**
 * Do all the math for OselinDevice struct
 * @param OselinDevice to be calculated
 * @param bool for set automatically the offset for centering the drawing
 **/
int oselin_trigonometry(OselinDevice *dev, bool automaticoffset){

    if (dev == NULL){
        cout <<errors(9) << endl;
        return 1;
    }

    trigfloors(dev, "down");

   
    trigwheel(dev, "rear");
    trigwheel(dev, "front");

    trigjoint(dev, "rear");
    trigjoint(dev, "front");
    
    if (dev->param.nfloors > 1){
        trigfloors(dev, "up");
        trigaxis(dev, "rear");
        trigaxis(dev, "front");
    }

    dev->absx = dev->rearjoint.head.x;
    dev->absy = dev->rearjoint.head.y;
    dev->abslength = dev->param.length + 2*dev->rearjoint.length - 2* dev->rearjoint.head.radius;
    if (automaticoffset){
        dev->offset = (dev->param.svgwidth - dev->downfloor.width)/2;
    }
    return 0;
}





oselin::Svg::Svg(Svg &s){
    this->x_ =           s.x();
    this->y_ =           s.y();
    this->stroke_ =      s.stroke();
    this->color_ =       s.color();
    this->strokecolor_ = s.strokecolor();
}
oselin::Wheel::Wheel(Wheel &w): oselin::Svg(w){
    this->radius_ = w.radius();
    this->innercolor_ = w.innercolor();
}
oselin::Floor::Floor(Floor &f): oselin::Svg(f){
    this->width_ =  f.width();
    this->height_ = f.height();
}
oselin::Joint::Joint(Joint &j): oselin::Svg(j){
    this->length_ = j.length();
    this->body = j.body;
    this->head = j.head;
}
oselin::Axis::Axis(Axis &a): oselin::Svg(a){
    this->body =         a.body;
    this->bottom_screw = a.bottom_screw;
    this->top_screw =    a.top_screw;
    this->angle_ =       a.angle();
    //this->point_ =       a.point();
}

oselin::Trailer::Trailer(Trailer &t){
    cout << "Reference constructor has been invoked" << endl;
    this->svg_ =        t.svg();
    this->length_ =     t.length();
    this->x_ =          t.x();
    this->y_ =          t.y();
    this->offset_ =     t.offset();
    this->downfloor =   t.downfloor;
    this->upfloor =     t.upfloor;
    this->front_wheel = t.front_wheel;
    this->rear_wheel =  t.rear_wheel;
    this->rear_joint =  t.rear_joint;
    this->front_joint = t.front_joint;
    this->rear_axis =   t.rear_axis;
    this->front_axis =  t.front_axis;
    this->parameters_ = t.parameters();
}
oselin::Trailer::Trailer(Trailer *t){
    cout << "Pointer constructor has been invoked" << endl;
    this->svg_ =        t->svg();
    this->length_ =     t->length();
    this->x_ =          t->x();
    this->y_ =          t->y();
    this->offset_ =     t->offset();
    this->downfloor =   t->downfloor;
    this->upfloor =     t->upfloor;
    this->front_wheel = t->front_wheel;
    this->rear_wheel =  t->rear_wheel;
    this->rear_joint =  t->rear_joint;
    this->front_joint = t->front_joint;
    this->rear_axis =   t->rear_axis;
    this->front_axis =  t->front_axis;
    this->parameters_ = t->parameters();
}
oselin::Trailer::Trailer(unordered_map<string,float> parameters, bool avoid_svg){
    cout << "Constructor has been invoked" << endl;
    /**
     * @param parameters
     * margin
     * radius
     * length
    **/

 
    if (parameters["car_radius"] < 16 || parameters["car_radius"] > 18){
        throw std::out_of_range("Radius value is wrong!");
    }

    //Estimating the required margin values
    parameters["margin"] = parameters["car_length"]/2;

    //Redefining length and height
    parameters["trailer_length"] = parameters["car_length"] * parameters["n_cars"] 
                           + (parameters["n_cars"]+3) * parameters["length"]/2;

    parameters["trailer_height"] = parameters["car_height"] * parameters["n_floors"] + 100;

    
    //CONSTRAINTS
    if (!avoid_svg){
        if (parameters["svg_width"] < parameters["trailer_length"]){
            throw std::invalid_argument("INIT: WIDTH ERROR");
        }
        if (parameters["svg_height"] < parameters["trailer_height"]*5/4){
            throw std::invalid_argument("INIT: HEIGHT ERROR");
        }
    }
    if (parameters["n_cars"] == 1 && parameters["n_floors"] == 2){
        throw std::invalid_argument("INIT: STRUCTURAL ERROR");
    }
    if (parameters["car_length"] < (parameters["car_height"]*4/5)){
        throw std::invalid_argument("INIT: CAR DIMENSIONS ERROR");
    }
    if (parameters["n_cars"] > 2){
        throw std::out_of_range("Too many cars!");
    }
    if (parameters["n_floors"] > 2){
        throw std::out_of_range("Too many floors!");
    }

    
    this->parameters_ = parameters;
}
oselin::Trailer::Trailer(string s){}
string oselin::Trailer::svg() const{
    //ToDo
}

