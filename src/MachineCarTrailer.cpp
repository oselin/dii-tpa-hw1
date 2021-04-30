#include "car_trailer.h"
#include "machine_car_trailer.h"
#include <iostream>
#include <string>
#include <cmath>
#include "Car.h"

#include <fstream>
#include <streambuf>
#include <sstream>

using namespace std;

//bool are_equal(OselinMachine *, OselinMachine *);


//IMPLEMENTING @GIACOMOCORRADINI CAR.H LIBRARY
/**
 * Initializate car struct
 * @param float[] -> parameters for the design
 * @param newx, newy car's position
 **/
coca_device * oselin_coca_init(float param[6], float newx, float newy){
    

    parametri arrayparam;
    arrayparam.inwidth  = param[0];
    arrayparam.inheight = param[1];
    arrayparam.indiam   = param[2];
    arrayparam.inpx  = newx;
    arrayparam.inpy  = newy - param[2];
    arrayparam.inass    = 1;

    //(macch->car.height - 1) / 2;
    coca_device * dev = coca_init_device(arrayparam);
    coca_try_finestrini(dev);
    coca_try_spoiler(dev);
    coca_try_tetto(dev);
    //oselin_coca_implementation(dev, newparam);

    return dev;
}

//MACHINE
/**
 * Initialize a machine
 * @param OselinDevice trailers can be copied from
 * @param int -> number of trailers chosen by the user
 * @param float[] ->list of parameters chosen by the user:
 * LENGTH | HEIGHT | RADIUS | NCARS-PER-TRAILER | NFLOORS
 **/
OselinMachine * oselin_machine_init(OselinDevice *dev, int ntrailers, float parameters[5]){

        
    if (!oselin_init(dev, parameters, true)){
        //CHECKING CONSTRAINTS AND SETTING SVG DIMENSIONS
        dev->param.svgheight = 3 * dev->param.height;
        oselin_trigonometry(dev, false);
        dev->param.svgwidth = (ntrailers +1) * dev->abslength;
        dev->offset = 0.5 * dev->abslength;
        oselin_to_svg(dev);


        // DYNAMIC ARRAY SOLUTION FOR THEN MACHINE
        OselinMachine *machine = new OselinMachine;
        machine->length = ntrailers;
        for (int i=0; i<5; i++) machine->parameters[i] = parameters[i];
        machine->trailerarray = new OselinDevice* [ntrailers];        

        machine->cararray = new coca_device* [(int)parameters[4]*(int)parameters[3]*ntrailers];
        
        machine->svg = dev->svg;
        for (int i=0; i< ntrailers; i++){
            machine->trailerarray[i] = oselin_init_acopyof(dev);
            machine->trailerarray[i]->offset = (0.5 + i) * dev->abslength;
            oselin_to_svg(machine->trailerarray[i], false);
        }
             
        float x,y;
        for (int i=0; i < (int)parameters[4]; i++){
            for (int j=0; j< (int)parameters[3]*ntrailers; j++){
                int index = j/(int)parameters[3];      
                y = dev->absy - 1.5*dev->downfloor.height - (i)*dev->param.height - (parameters[1]-1)/2;
                x = machine->trailerarray[index]->offset + machine->trailerarray[index]->param.margin + (j%(int)parameters[3]) * (machine->trailerarray[index]->param.length - 2* machine->trailerarray[index]->param.margin - parameters[0]);
                machine->cararray[i*(int)parameters[3]*ntrailers + j] = oselin_coca_init(parameters, x, y);   
            }
        }
        return machine;
        
    }
    return NULL;
}

/**
 * Convert all the attributes to svg format
 * @param OselinMachine to be converted
 * @param bool for adding or not header
 **/
string oselin_machine_to_string(OselinMachine *mach, bool with_header){
    
    if (mach!=NULL){
        string svg = "";
        if (with_header){
        svg += "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n<svg xmlns='http://www.w3.org/2000/svg' width='";
        svg += to_string(mach->trailerarray[0]->param.svgwidth) + " '  height='";
        svg += to_string(mach->trailerarray[0]->param.svgheight) + "' >";
        svg += "<rect  x='0.000000' y='0.000000' width='" + to_string(mach->trailerarray[0]->param.svgwidth) + "' height='" + to_string(mach->trailerarray[0]->param.svgheight) + "' style='stroke-width:0.0; stroke:' fill='white' />";
        }
        int len = mach->length;
        for (int i=0;i<mach->parameters[4];i++){
            for (int j=0;j < (int)mach->parameters[3]*len; j++ ){
                svg += "<!--COCADEVICECAR-->\n";
                svg += coca_strg_device(mach->cararray[i*(int)mach->parameters[3]*len + j],0,0);

            }
        }
        for (int i=0; i< len; i++) {
            svg += "<!--OSELINDEVICETRAILER-->\n";
            svg += mach->trailerarray[i]->svg;
        }
        //mach->svg = svg;
        return svg;
    }
    return "";
}

/**
 * Save the created machine to file
 * @param OselinMachine to be saved
 **/
string oselin_machine_save(OselinMachine *mach){
    cout << (mach == NULL) << endl;
    if (mach->parameters[0] != 0 && mach != NULL){
        string filename, svgmach;
        cout << "File name for saving (with extension): ";
        cin >> filename;
        ofstream MyFile(filename);
        svgmach =  oselin_machine_to_string(mach, true);
        if (svgmach == "") return "Something went wrong.";
        else{
            MyFile << (svgmach + "\n</svg>");
            MyFile.close();
            return "Saved!";
        }
    }
    return "The machine looks empty...";
    
}

/**
 * Parse an svg imported from file
 * @param OselinMachine to be filled
 * @param string to be parsed
 **/
void oselin_machine_parsing(OselinMachine *mach, string svg){
    cout << svg << endl;
    if (svg!=""){
        int pieces[mach->length][2];
        int index = 0;
        for (int i=0;i<mach->length;i++){
            index = svg.find("<!--OSELINDEVICETRAILER-->",index);
            int len = svg.find("<!--OSELINDEVICETRAILER-->",index+30) - index;
            pieces[i-1][0] = index;
            pieces[i-1][1] = len;
            oselin_parsing(mach->trailerarray[i],svg.substr(index,len));
        }
    }
}