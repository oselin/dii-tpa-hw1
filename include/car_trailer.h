
#ifndef CAR_TRAILER_H
#define CAR_TRAILER_H


#include <string>

struct OselinDevice{
    double constr;
    float width;
    float height;
};

struct Oselin_Wheel{

    float x;
    float y;
    float radius;
    float stroke;
    std::string strokecolor;
    std::string outercolor;
    std::string innercolor;

};

struct Oselin_Floor{
    float x;
    float y;
    float width;
    float height;
    float stroke;
    std::string strokecolor;
    std::string fillingcolor;
};

struct Oselin_Joint{

    Oselin_Floor body;
    
    Oselin_Wheel head;
};

struct Oselin_Axis{
    Oselin_Floor body;

    float angle;
};

std::string oselin_stringwheels(Oselin_Wheel, Oselin_Wheel);

std::string oselin_stringfloors(Oselin_Floor, Oselin_Floor);

std::string oselin_stringaxis(Oselin_Axis, Oselin_Axis);

std::string oselin_stringjoints(Oselin_Joint, Oselin_Joint);

void oselin_trigonometry();

int oselin_init();

std::string oselin_to_svg(OselinDevice);


#endif //CAR_TRAILER_H
