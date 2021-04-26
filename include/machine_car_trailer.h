#ifndef MACHINE_CAR_TRAILER_H
#define MACHINE_CAR_TRAILER_H

#include <string>
#include "../TpaHomework1/include/Car.h"

void oselin_coca_implementation(coca_device *, float[5]);    

std::string oselin_coca_to_svg(coca_device *);

coca_device * oselin_coca_init(float[5], float, float);

#endif //MACHINE_CAR_TRAILER_H