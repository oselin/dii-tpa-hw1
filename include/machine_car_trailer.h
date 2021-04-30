#ifndef MACHINE_CAR_TRAILER_H
#define MACHINE_CAR_TRAILER_H

#include <string>
#include "../TpaHomework1/include/Car.h"
#include "car_trailer.h"


struct OselinMachine{
    OselinDevice ** trailerarray;
    coca_device  ** cararray;
    std::string svg;
    Parameters parameters;
    int length;
};

/**
 * Initializate car struct
 * @param float[] -> parameters for the design
 * @param newx, newy car's position
 **/
coca_device * oselin_coca_init(Parameters, float, float);

/**
 * Initialize a machine
 * @param OselinDevice trailers can be copied from
 * @param int -> number of trailers chosen by the user
 * @param float[] ->list of parameters chosen by the user:
 * LENGTH | HEIGHT | RADIUS | NCARS-PER-TRAILER | NFLOORS
 **/
OselinMachine * oselin_machine_init(Parameters, int );

/**
 * Convert all the attributes to svg format
 * @param OselinMachine to be converted
 * @param bool for adding or not header
 **/
std::string oselin_machine_to_string(OselinMachine *, bool=true);

/**
 * Save the created machine to file
 * @param OselinMachine to be saved
 **/
std::string oselin_machine_save(OselinMachine *mach);

/**
 * Parse an svg imported from file
 * @param OselinMachine to be filled
 * @param string to be parsed
 **/
void oselin_machine_parsing(OselinMachine *, std::string);
#endif //MACHINE_CAR_TRAILER_H