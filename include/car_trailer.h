
#ifndef CAR_TRAILER_H
#define CAR_TRAILER_H

#define DOWNOFFSET 50
#include <string>
#include <unordered_map>


using std::unordered_map;
using std::string;

unordered_map<std::string,float> parameters;

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
            //Svg(){}
            //Deconstructor;
            
            void  x(float inp);
            float x();

            void  y(float inp);
            float y();
            
            void  stroke(float inp);
            float stroke();

            void   color(string inp);
            string color();

            void   strokecolor(string inp);
            string strokecolor();
    };

    class Wheel: public Svg{
        private:
            float radius_;
            string innercolor_;
        public:
            Wheel(){}

            void  radius(float r);
            float radius();
            //Deconstructor;

    };

    class Floor: public Svg{
        private:
            float width_;
            float height_;
        public:
            void  width(float w);
            float width();
            void  height(float h);
            float height();
    };

    class Joint: public Svg{
        private:
            float length_;
            Floor body;
            Floor head;
        public:
            void  length(float l);
            float length();

    };

    class Axis{
        private:
            Floor body;
            Wheel bottom;
            Wheel top;
            float angle_ = 20;
            float point_;
        public:
            void  angle(float a);
            float angle();
            void  point(float p);
            float point();
    };

    class Trailer{
        private:
            string svg;
            float length;
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

        public:
            Trailer(unordered_map<string,float> parameters, bool avoid_svg);

    };
};


void  oselin::Svg::x(float inp){this->x_ = inp;}

float oselin::Svg::x(){return this->x_;}

void  oselin::Svg::y(float inp){this->y_ = inp;}

float oselin::Svg::y(){return this->y_;}

void  oselin::Svg::stroke(float inp){this->stroke_ = inp;}

float oselin::Svg::stroke(){return this->stroke_;}

void  oselin::Svg::color(string inp){this->color_ = inp;}

string oselin::Svg::color(){return this->color_;}

void  oselin::Svg::strokecolor(string inp){this->strokecolor_ = inp;}

string oselin::Svg::strokecolor(){return this->strokecolor_;}

void  oselin::Wheel::radius(float r){this->radius_ = r;}

float oselin::Wheel::radius(){return this->radius_;}

void  oselin::Floor::width(float w){this->width_ = w;}

float oselin::Floor::width(){return this->width_;}

void  oselin::Floor::height(float h){this->height_ = h;}

float oselin::Floor::height(){return this->height_;}

void  oselin::Joint::length(float l){this->length_ = l;}

float oselin::Joint::length(){return this->length_;}

void  oselin::Axis::angle(float a){this->angle_ = a;}

float oselin::Axis::angle(){return this->angle_;}

void  oselin::Axis::point(float p){this->point_ = p;}

float oselin::Axis::point(){return this->point_;}

#endif //CAR_TRAILER_H
