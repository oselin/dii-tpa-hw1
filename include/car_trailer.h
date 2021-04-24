
#ifndef CAR_TRAILER_H
#define CAR_TRAILER_H

#define WHEELOFFSET 70
#define DOWNOFFSET 50
#include <string>

struct Parameters{
    float svgwidth;
    float svgheight;
    float radius;
    float length;
    float height;
    int ncars;
    int nfloors;
};

struct Oselin_Wheel{

    float x;
    float y;
    float radius;
    float stroke;
    std::string strokecolor = "black";
    std::string outercolor  = "black";
    std::string innercolor  = "gray";

};

struct Oselin_Floor{
    float x;
    float y;
    float width;
    float height;
    float stroke;
    std::string strokecolor  = "black";
    std::string fillingcolor = "#990000";
};

struct Oselin_Joint{
    
    float length;
    Oselin_Floor body;
    Oselin_Wheel head;
};

struct Oselin_Axis{
    
    Oselin_Floor body;
    Oselin_Wheel bottomscrew;
    Oselin_Wheel topscrew;
    float angle = 20;
    float rotationpoint[2];
};

struct OselinDevice{

    std::string svg;
    Parameters param;
    float abslength;
    float absx;
    float absy;
    Oselin_Floor downfloor;
    Oselin_Floor upfloor;
    Oselin_Wheel frontwheel;
    Oselin_Wheel rearwheel;
    Oselin_Joint rearjoint;
    Oselin_Joint frontjoint;
    Oselin_Axis rearaxis;
    Oselin_Axis frontaxis;
};

std::string oselin_to_svg(OselinDevice *, bool, bool, float);

void oselin_trigonometry(OselinDevice *);

int oselin_init(OselinDevice *, float[5]);

void oselin_parsing(OselinDevice *, std::string);

void errors(int);

//SET FUNCTIONS
int oselin_set(OselinDevice *, float [5]);


#endif //CAR_TRAILER_H
