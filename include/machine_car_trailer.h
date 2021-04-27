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

/**
 * Fill some parameters which weren't considered or modified by the author @GiacomoCorradini
 * @param coca_device (=car)
 * @param param from which newparam can be calculated
 **/
void oselin_coca_implementation(coca_device *, float[5]);    

/**
 * Convert car to svg
 * @param coca_device (or car struct)
 **/
std::string oselin_coca_to_svg(coca_device *);

/**
 * Initializate car struct
 * @param float[] -> parameters for the design
 * @param newx, newy car's position
 **/
coca_device * oselin_coca_init(float[5], float, float);

/**
 * Initialize a machine
 * @param OselinDevice trailers can be copied from
 * @param int -> number of trailers chosen by the user
 * @param float[] ->list of parameters chosen by the user:
 * LENGTH | HEIGHT | RADIUS | NCARS-PER-TRAILER | NFLOORS
 **/
OselinMachine * oselin_machine_init(OselinDevice *, int , float[5]);

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