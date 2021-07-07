
#ifndef CAR_TRAILER_H
#define CAR_TRAILER_H

#define DOWNOFFSET 50
#include <string>
#include <unordered_map>
#include <iostream>

using std::endl;
using std::cout;
using std::unordered_map;
using std::string;



namespace oselin{
    class Svg{
        protected:
            float x_;
            float y_;
            float stroke_;
            string color_;
            string strokecolor_;
        public:
            Svg(){}
            Svg(Svg &s);
            //Deconstructor;
            
            inline void   x(float &inp);
            inline void   x(float inp);
            inline float  x() const;
            inline void   y(float &inp);
            inline void   y(float inp);
            inline float  y() const;
            inline void   stroke(float &inp);
            inline void   stroke(float inp);
            inline float  stroke() const;
            inline void   color(string &inp);
            inline void   color(string inp);
            inline string color() const;
            inline void   strokecolor(string &inp);
            inline void   strokecolor(string inp);
            inline string strokecolor() const;
    };

    class Wheel: public Svg{
        private:
            float radius_;
            string innercolor_;
        public:
            Wheel(){}
            Wheel(Wheel &w);

            //inline void   radius(float &r);
            inline void   radius(float r);
            inline float  radius() const;
            //inline void   innercolor(string &in);
            inline void   innercolor(string in);
            inline string innercolor() const;
            //Deconstructor;

    };

    class Floor: public Svg{
        private:
            float width_;
            float height_;
        public:
            Floor(){}
            Floor (Floor &f);
            //inline void  width(const float &&w);
            inline void  width(float w);
            inline float width() const;
            //inline void  height(float &h);
            inline void  height(float h);
            inline float height() const;
    };

    class Joint: public Svg{
        private:
            float length_;
            Floor body;
            Floor head;
        public:
            Joint(){}
            Joint(Joint &j);
            //inline void  length(float &l);
            inline void  length(float l);
            inline float length() const;

    };

    class Axis:  public Svg{
        private:
            Floor body;
            Wheel bottom_screw;
            Wheel top_screw;
            float angle_ = 20;
            float point_[2];
        public:
            Axis(){}
            Axis (Axis &a);
            //inline void  angle(float &a);
            inline void  angle(float a);
            inline float angle() const;
            //inline void  point(float &p);
            inline void  point(float p);
            inline float point() const;
    };

    class Trailer{
        private:
            float length_;
            float x_;
            float y_;
            float offset_;

            Floor downfloor;
            Floor upfloor;
            Wheel front_wheel;
            Wheel rear_wheel;
            Joint rear_joint;
            Joint front_joint;
            Axis rear_axis;
            Axis front_axis;

            unordered_map<std::string,float> parameters_;
        public:
            Trailer(){}
            Trailer(unordered_map<string,float> parameters, bool avoid_svg = 0);
            Trailer (Trailer &t);
            Trailer (Trailer *t);
            Trailer (string s);

            //inline void  x(float &inp);
            inline void  x(float inp);
            inline float x() const;
            //inline void  y(float &inp);
            inline void  y(float inp);
            inline float y() const;
            //inline void  length(float &off);
            inline void  length(float off);
            inline float length() const;
            //inline void  offset(float &off);
            inline void  offset(float off);
            inline float offset() const;
            inline string svg() const;
            inline void  parameters(unordered_map<string, float> p);
            inline unordered_map<string, float> parameters() const;
            inline void  svg_width(float nv);  
            inline float svg_width() const;    
            inline void  svg_height(float nv); 
            inline float svg_height() const;
            inline void  trailer_length(float nv); 
            inline float trailer_length() const; 
            inline void  trailer_height(float nv); 
            inline float trailer_height() const; 
            inline void  car_length(float nv); 
            inline float car_length() const;   
            inline void  car_height(float nv);  
            inline float car_height() const;    
            inline void  car_radius(float nv);  
            inline float car_radius() const;   
            inline void  n_cars(float nv);     
            inline float n_cars() const;       
            inline void  n_floors(float nv);   
            inline float n_floors() const;     
    };

    class Machine{
        private:

        public:
    };

};



//void   oselin::Svg::x(float &inp){this->x_ = inp;}
void   oselin::Svg::x(float inp){this->x_ = inp;}
float  oselin::Svg::x() const{return this->x_;}
//void   oselin::Svg::y(float &inp){this->y_ = inp;}
void   oselin::Svg::y(float inp){this->y_ = inp;}
float  oselin::Svg::y() const{return this->y_;}
//void   oselin::Svg::stroke(float &inp){this->stroke_ = inp;}
void   oselin::Svg::stroke(float inp){this->stroke_ = inp;}
float  oselin::Svg::stroke() const{return this->stroke_;}
//void   oselin::Svg::color(string &inp){this->color_ = inp;}
void   oselin::Svg::color(string inp){this->color_ = inp;}
string oselin::Svg::color() const{return this->color_;}
//void   oselin::Svg::strokecolor(string &inp){this->strokecolor_ = inp;}
void   oselin::Svg::strokecolor(string inp){this->strokecolor_ = inp;}
string oselin::Svg::strokecolor() const{return this->strokecolor_;}

//void   oselin::Wheel::radius(float &r){this->radius_ = r;}
void   oselin::Wheel::radius(float r){this->radius_ = r;}
float  oselin::Wheel::radius() const{return this->radius_;}
//void   oselin::Wheel::innercolor(string &in){this->innercolor_ = in;}
void   oselin::Wheel::innercolor(string in){this->innercolor_ = in;}
string oselin::Wheel::innercolor() const{return this->innercolor_;}

//void   oselin::Floor::width(const float &&w){cout <<"byReference"<<endl;this->width_ = w;}
void   oselin::Floor::width(float w){this->width_ = w;}
float  oselin::Floor::width() const{return this->width_;}
//void   oselin::Floor::height(float &h){this->height_ = h;}
void   oselin::Floor::height(float h){this->height_ = h;}
float  oselin::Floor::height() const{return this->height_;}

//void   oselin::Joint::length(float &l){this->length_ = l;}
void   oselin::Joint::length(float l){this->length_ = l;}
float  oselin::Joint::length() const{return this->length_;}

//void   oselin::Axis::angle(float &a){this->angle_ = a;}
void   oselin::Axis::angle(float a){this->angle_ = a;}
float  oselin::Axis::angle() const{return this->angle_;}
//void   oselin::Axis::point(float p[]){this->point_ = p;}
//float  oselin::Axis::point() const{return this->point_;}

//void   oselin::Trailer::x(float &inp){this->x_ = inp;}
void   oselin::Trailer::x(float inp){this->x_ = inp;}
float  oselin::Trailer::x() const{return this->x_;}
//void   oselin::Trailer::y(float &inp){this->y_ = inp;}
void   oselin::Trailer::y(float inp){this->y_ = inp;}
float  oselin::Trailer::y() const{return this->y_;}
//void   oselin::Trailer::length(float &l){this->length_ = l;}
void   oselin::Trailer::length(float l){this->length_ = l;}
float  oselin::Trailer::length() const{return this->length_;}
//void   oselin::Trailer::offset(float &off){this->offset_ = off;}
void   oselin::Trailer::offset(float off){this->offset_ = off;}
float  oselin::Trailer::offset() const{return this->offset_;}
void  oselin::Trailer::parameters(unordered_map<string, float> p){this->parameters_ = p;}
unordered_map<string, float> oselin::Trailer::parameters() const{return this->parameters_;}

void  oselin::Trailer::svg_width(float nv){this->parameters_["svg_width"] = nv;}  
float oselin::Trailer::svg_width() const{return this->parameters_["svg_width"];} 
void  oselin::Trailer::svg_height(float nv){this->parameters_["svg_height"] = nv;}
float oselin::Trailer::svg_height() const{return this->parameters_["svg_height"];}
void  oselin::Trailer::trailer_length(float nv){this->parameters_["trailer_length"] = nv;}
float oselin::Trailer::trailer_length() const{return this->parameters_["trailer_length"];}
void  oselin::Trailer::trailer_height(float nv){this->parameters_["trailer_height"] = nv;}
float oselin::Trailer::trailer_height() const{return this->parameters_["trailer_height"];}
void  oselin::Trailer::car_length(float nv){this->parameters_["car_length"] = nv;}
float oselin::Trailer::car_length() const{return this->parameters_["car_length"];}
void  oselin::Trailer::car_height(float nv){this->parameters_["car_height"] = nv;}
float oselin::Trailer::car_height() const{return this->parameters_["car_height"];}
void  oselin::Trailer::car_radius(float nv){this->parameters_["car_radius"] = nv;}
float oselin::Trailer::car_radius() const{return this->parameters_["car_radius"];}
void  oselin::Trailer::n_cars(float nv){this->parameters_["n_cars"] = nv;}
float oselin::Trailer::n_cars() const{return this->parameters_["n_cars"];}
void  oselin::Trailer::n_floors(float nv){this->parameters_["n_floors"] = nv;}
float oselin::Trailer::n_floors() const{return this->parameters_["n_floors"];}
#endif //CAR_TRAILER_H
