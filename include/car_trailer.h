
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
    struct Parameters{
        bool isempty = true;
        float x_                = 0;//TO AVOID RANDOM UNDEFINED VALUES
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
        public:
            Svg(){}
            Svg(Svg &s);
            ~Svg(){}
            
            void   x(float inp);
            float  x() const;
            
            void   y(float inp);
            float  y() const;
            
            void   stroke(float inp);
            float  stroke() const;
            
            void   color(string inp);
            string color() const;
            
            void   strokecolor(string inp);
            string strokecolor() const;
            
            void  offset(float off);
            float offset() const;

            virtual string svg() const = 0; // PURE VIRTUAL FUNCTION
    };

    class Wheel: public Svg{
        private:
            float radius_;
            string innercolor_;
        public:
            Wheel();
            Wheel(Wheel &w);

            void   radius(float r);
            float  radius() const;

            void   innercolor(string in);
            string innercolor() const;

            string svg() const;
    };

    class Floor: public Svg{
        private:
            float width_;
            float height_;
        public:
            Floor();
            Floor (Floor &f);
            
            void  width(float w);
            float width() const;
            
            void  height(float h);
            float height() const;

            string svg() const;
    };

    class Joint: public Svg{
        private:
            float length_;
        public:
            Joint(){}
            Joint(Joint &j);

            Floor body;
            Wheel head;
            
            void  length(float l);
            float length() const;
            
            string svg() const;

    };

    class Axis:  public Svg{
        private:
            float angle_ = 20;
            float point_[2];
        public:
            Axis(){}
            Axis (Axis &a);

            Floor body;
            Wheel bottom_screw;
            Wheel top_screw;
            
            void  angle(float a);
            float angle() const;
            
            void point_x(float px);
            void point_y(float py);
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

            Trailer(){}
            Trailer(Parameters parameters, bool avoid_svg = 0);
            Trailer (Trailer &t);
            Trailer (Trailer *t);
            Trailer (string s);

            //inline void  x(float &inp);
            void  x(float inp);
            float x() const;
            //inline void  y(float &inp);
            void  y(float inp);
            float y() const;
            //inline void  length(float &off);
            void  length(float off);
            float length() const;
            
            void   height(float h);
            float  height() const;

            void  offset(float off);
            float offset() const;
            string svg(bool = false, bool = false) const;
            void  parameters(Parameters p);
            Parameters parameters() const;
            void  svg_width(float nv);  
            float svg_width() const;    
            void  svg_height(float nv); 
            float svg_height() const;
            void  trailer_length(float nv); 
            float trailer_length() const; 
            void  trailer_height(float nv); 
            float trailer_height() const; 
            void  car_length(float nv); 
            float car_length() const;   
            void  car_height(float nv);  
            float car_height() const;    
            void  car_radius(float nv);  
            float car_radius() const;   
            void  n_cars(float nv);     
            float n_cars() const;       
            void  n_floors(float nv);   
            float n_floors() const;

            void copy();
    };

    class Machine{
        private:

        public:
    };

    int trigonometry(Trailer *trailer, bool = 1);
};



#endif //CAR_TRAILER_H
