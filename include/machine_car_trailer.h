#ifndef MACHINE_CAR_TRAILER_H
#define MACHINE_CAR_TRAILER_H

#include <string>
#include "../TpaHomework1/include/Car.h"
#include "car_trailer.h"


struct OselinMachine{
    OselinDevice ** trailerarray;
    coca_device  ** cararray;
    std::string svg;
    float parameters[5];
    int length;
};

void oselin_coca_implementation(coca_device *, float[5]);    

std::string oselin_coca_to_svg(coca_device *);

coca_device * oselin_coca_init(float[5], float, float);


OselinMachine * oselin_machine_init(OselinDevice *, int , float[5]);

std::string oselin_machine_to_string(OselinMachine *, bool=true);

std::string oselin_machine_save(OselinMachine *mach);

std::string oselin_machine_change(OselinMachine *, float[5]);
#endif //MACHINE_CAR_TRAILER_H