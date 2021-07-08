
#ifndef CAR_TRAILER_H
#define CAR_TRAILER_H

#define DOWNOFFSET 50
#define FRONT 1
#define REAR  0
#define UP    1 
#define DOWN  0

#include <string>
#include <unordered_map>
#include <iostream>
#include <ostream>

using std::unordered_map;
using std::string;
using std::ostream;



namespace oselin{
    struct Parameters{
        bool isempty_ = true;
        float x_                = 0;//TO AVOID UNDEFINED RANDOM VALUES
        float y_                = 0;
        float length_           = 0;
        float height_           = 0;
        float offset_           = 0;
        float svg_width_        = 0;
        float svg_height_       = 0;
        float trailer_length_   = 0;
        float trailer_height_   = 0;  
        float car_length_       = 0;
        float car_height_       = 0;  
        float car_radius_       = 0; 
        float n_cars_           = 0;  
        float n_floors_         = 0;
        float margin_           = 0;
    };
    
    class Svg{
        protected:
            float x_ ;
            float y_;
            float stroke_;
            string color_;
            string strokecolor_;
            float offset_ = 0;

            virtual void print(ostream&) const;
        public:
            Svg(){}
            Svg(Svg &);
            ~Svg(){}
            
            void   x(float);
            float  x() const;
            
            void   y(float);
            float  y() const;
            
            void   stroke(float);
            float  stroke() const;
            
            void   color(string);
            string color() const;
            
            void   strokecolor(string);
            string strokecolor() const;
            
            void  offset(float);
            float offset() const;
            
            virtual string svg() const = 0; // PURE VIRTUAL FUNCTION

            friend ostream& operator<<(ostream& os, const Svg &mother){
                mother.print(os);
                return os;
            }
    };

    class Wheel: public Svg{
        private:
            float radius_;
            string innercolor_;

            void print(ostream&) const;
        public:
            Wheel();
            Wheel(Wheel &);
            Wheel(string, float = 0);

            void   radius(float);
            float  radius() const;

            void   innercolor(string);
            string innercolor() const;

            string svg() const;
    };

    class Floor: public Svg{
        private:
            float width_;
            float height_;

            void print(ostream&) const;
        public:
            Floor();
            Floor (Floor &);
            Floor(string, float = 0);
            
            void  width(float);
            float width() const;
            
            void  height(float);
            float height() const;

            string svg() const;
    };

    class Joint: public Svg{
        private:
            float length_;

            void print(ostream&) const;
        public:
            Joint();
            Joint(Joint &);
            Joint(string, float = 0);

            Floor body;
            Wheel head;
            
            void  length(float);
            float length() const;
            
            string svg() const;

    };

    class Axis:  public Svg{
        private:
            float angle_;
            float point_[2];

            void print(ostream&) const;
        public:
            Axis();
            Axis (Axis &);
            Axis(string, float = 0);
            
            Floor body;
            Wheel bottom_screw;
            Wheel top_screw;
            
            void  angle(float);
            float angle() const;
            
            void point_x(float);
            void point_y(float);
            float* point();
            
            string svg() const;
    };

    class Trailer{
        private:
            Parameters parameters_;

        public:
            
            Floor downfloor;    
            Floor upfloor;      
            Wheel front_wheel;  
            Wheel rear_wheel;   
            Joint rear_joint;   
            Joint front_joint;  
            Axis  rear_axis;    
            Axis  front_axis;   

            Trailer();
            Trailer(Parameters, bool = 0);
            Trailer (Trailer &);
            Trailer (Trailer *);
            Trailer (string);

            void isempty(bool);
            bool isempty() const;
            void  x(float);
            float x() const;
            void  y(float);
            float y() const;
            void  length(float);
            float length() const;
            void   height(float);
            float  height() const;
            void  offset(float);
            float offset() const;

            string svg(bool = false, bool = false) const;
            void  parameters(Parameters);
            Parameters parameters() const;

            void  svg_width(float);  
            float svg_width() const;    
            void  svg_height(float); 
            float svg_height() const;
            void  trailer_length(float); 
            float trailer_length() const; 
            void  trailer_height(float); 
            float trailer_height() const; 
            void  car_length(float); 
            float car_length() const;   
            void  car_height(float);  
            float car_height() const;    
            void  car_radius(float);  
            float car_radius() const;   
            void  n_cars(float);     
            float n_cars() const;       
            void  n_floors(float);   
            float n_floors() const;
            void  margin(float);   
            float margin() const;
            void fromSvg2Param();
            void copy();
    };

    class Machine{
        private:

        public:
    };

    int trigonometry(Trailer *, bool = 1);

    string checkpoint(int);

    string buffering(string, string, char);

    string measures();

    void printParam(Parameters);
};

//ostream& operator<<(ostream& os, const oselin::Svg &mother){
//    mother.print(os);
//    return os;
//}

#endif //CAR_TRAILER_H
