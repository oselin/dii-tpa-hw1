
#ifndef CAR_TRAILER_H
#define CAR_TRAILER_H

#define DOWNOFFSET 50
#include <string>

struct Parameters{
    float svgwidth;
    float svgheight;
    float radius;
    float length;
    float height;
    int   ncars;
    int   nfloors;
    float margin;
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
    float offset;
    Oselin_Floor downfloor;
    Oselin_Floor upfloor;
    Oselin_Wheel frontwheel;
    Oselin_Wheel rearwheel;
    Oselin_Joint rearjoint;
    Oselin_Joint frontjoint;
    Oselin_Axis rearaxis;
    Oselin_Axis frontaxis;
};

/**
 * Convert the device into a string
 * @param OselinDevice to convert
 * @param bool for adding or not the header
 * @param bool to add or not measures
 **/
int oselin_to_svg(OselinDevice *, bool = true, bool = false);

/**
 * Do all the math for OselinDevice struct
 * @param OselinDevice to be calculated
 * @param bool for set automatically the offset for centering the drawing
 **/
int oselin_trigonometry(OselinDevice *, bool = true);

/**
 * Check if all the data are solid
 * @param OselinDevice to be filled
 * @param float with data to check
 * @param bool for bypassing some check operations
 **/
OselinDevice *oselin_init(Parameters, bool = false);

/**
 * Parse an svg imported as string and fill the device
 * @param string svg
 * @param device to be filled
 **/
void oselin_parsing(OselinDevice *, std::string);

/**
 * Function for handling errors. It returns a string with the error type. It is invoked by all the other functions
 * @param int error code
 **/
std::string errors(int);

/**
 * Allow changing in the device
 **/
OselinDevice *oselin_set_radius(OselinDevice *, float);
OselinDevice *oselin_set_length(OselinDevice *, float);
OselinDevice *oselin_set_height(OselinDevice *, float);
OselinDevice *oselin_set_ncars(OselinDevice *, int);
OselinDevice *oselin_set_nfloors(OselinDevice *, int);
OselinDevice *oselin_set_svgwidth(OselinDevice *, float);
OselinDevice *oselin_set_svgheight(OselinDevice *, float);

/**
 * Return device-like struct allowing several copies
 * @param device (=trailer already existing)
 **/
OselinDevice *oselin_init_acopyof(OselinDevice *);


#endif //CAR_TRAILER_H
