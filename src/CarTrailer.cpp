
#include "car_trailer.h"
#include <iostream>
#include <string>
#include <cmath>

#include <stdexcept>


using namespace std;

/**
 * Function for handling errors. It returns a string with the error type. It is invoked by all the other functions
 * @param int error code
 **/
string errors(int c){

    switch (c)
    {
    case 0:
        throw std::invalid_argument("INIT: WIDTH ERROR");
    case 1:
        throw std::invalid_argument("INIT: STRUCTURAL ERROR");
    case 2:
        throw std::invalid_argument("INIT: CAR DIMENSIONS ERROR");
    case 3:
        throw std::logic_error("You must create/load a device first!");
    case 4:
        throw std::invalid_argument("INIT: HEIGHT ERROR");
    case 5:
        throw std::invalid_argument("INIT: NCARS TOO LONG");
    case 6:
        throw std::invalid_argument("INIT: NFLOORS TOO HIGH");
        break;
    case 7:
        return "Check the parameters and try again" ;
        break;
    case 8:
        return "Something went wrong. " ;
        break;
    case 9:
        return "Fatal error.";
        break;
    default:
        break;
    }
    return "";
    //cout << "GOING BACK TO MAIN MENU" << endl;
}

/**
 * Check if all the data are solid
 * @param OselinDevice to be filled
 * @param float with data to check
 * @param bool for bypassing some check operations
 **/

oselin::Trailer::Trailer(unordered_map<string,float> parameters, bool avoid_svg){

    /**
     * @param parameters
     * margin
     * radius
     * length
    **/

 
    if (parameters["radius"] < 16 || parameters["radius"] > 18){
        throw std::out_of_range("Radius value is wrong!");
    }

    //Estimating the required margin values
    parameters["margin"] = parameters["length"]/2;

    //Redefining length and height
    parameters["length"] = parameters["length"] * parameters["n_cars"] 
                           + (parameters["n_cars"]+3) * parameters["length"]/2;

    parameters["height"] = parameters["height"] * parameters["n_floors"] + 100;

    
    //CONSTRAINTS
    if (!avoidsvg){
        if (parameters["svg_width"] < parameters["length"]){
            throw std::invalid_argument("INIT: WIDTH ERROR");
        }
        if (parameters["svg_height"] < parameters["height"]*5/4){
            throw std::invalid_argument("INIT: HEIGHT ERROR");
        }
    }
    if (parameters["n_cars"] == 1 && parameters["n_floors"] == 2){
        throw std::invalid_argument("INIT: STRUCTURAL ERROR");
    }
    if (parameters["length"] < (parameters["height"]*4/5)){
        throw std::invalid_argument("INIT: CAR DIMENSIONS ERROR");
    }
    if (parameters["n_cars"] > 2){
        throw std::out_of_range("Too many cars!");
    }
    if (parameters["n_floors"] > 2){
        throw std::out_of_range("Too many floors!");
    }

    
    this->parameters = parameters;
}
