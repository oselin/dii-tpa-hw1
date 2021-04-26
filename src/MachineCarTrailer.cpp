#include "car_trailer.h"
#include <iostream>
#include <string>
#include <cmath>
#include "Car.h"

using namespace std;

//bool are_equal(OselinMachine *, OselinMachine *);


//IMPLEMENTING @GIACOMOCORRADINI CAR.H LIBRARY

string new_coca_strg_ruote(coca_device* macch){
    string ruo;
    // Ruota sinistra
    ruo = "\t<circle ";
    ruo += "cx=\"" + to_string(macch->sx.centrox) + "\" cy=\"" + to_string(macch->sx.centroy) + "\" ";
    ruo += "r=\"" + to_string(macch->sx.ruota) + "\" stroke=\"black\" stroke-width=\"3\" fill=\"black\"/>\n\n";
    // Cerchione sinistra
    ruo += "\t<circle ";
    ruo += "cx=\"" + to_string(macch->sx.centrox) + "\" cy=\"" + to_string(macch->sx.centroy) + "\" ";
    ruo += "r=\"" + to_string(macch->sx.cerchione) + "\" stroke=\"black\" stroke-width=\"3\" fill=\"gray\"/>\n\n";
    // Ruota destra
    ruo += "\t<circle ";
    ruo += "cx=\"" + to_string(macch->dx.centrox) + "\" cy=\"" + to_string(macch->dx.centroy) + "\" ";
    ruo += "r=\"" + to_string(macch->dx.ruota) + "\" stroke=\"black\" stroke-width=\"3\" fill=\"black\"/>\n\n";
    // Cerchione destra
    ruo += "\t<circle ";
    ruo += "cx=\"" + to_string(macch->dx.centrox) + "\" cy=\"" + to_string(macch->dx.centroy) + "\" ";
    ruo += "r=\"" + to_string(macch->dx.cerchione) + "\" stroke=\"black\" stroke-width=\"3\" fill=\"gray\"/>\n\n";

    return ruo;
}

void oselin_coca_implementation(coca_device * macch, float param[5]){
    
    //coca_try_carrozzeria(coca_device * macch)
    macch->car.width = param[0];
    macch->car.height = param[1];
    macch->car.cx = param[3];
    macch->car.cy = param[4];

    int diametro = (int)param[2];
    int x = 1;//(int)param[5];
    
    //coca_try_ruote(coca_device *macch)
    switch (diametro)
    {
        case 16:
            macch->sx.ruota = (macch->car.height - 1) / 2;
            macch->sx.cerchione = macch->sx.ruota / 1.6;
            macch->dx.ruota = (macch->car.height - 1) / 2;
            macch->dx.cerchione = macch->dx.ruota / 1.6;
            break;
        case 17:
            macch->sx.ruota = macch->car.height / 2;
            macch->sx.cerchione = macch->sx.ruota / 1.6;
            macch->dx.ruota = macch->car.height / 2;
            macch->dx.cerchione = macch->dx.ruota / 1.6;
            break;
        case 18:
            macch->sx.ruota = (macch->car.height + 1) / 2;
            macch->sx.cerchione = macch->sx.ruota / 1.6;
            macch->dx.ruota = (macch->car.height + 1) / 2;
            macch->dx.cerchione = macch->dx.ruota / 1.6;
            break;
        
        default:
            break;
    }

    //coca_try_assetto(coca_device* macch)
    switch (x){
        case 1:
            macch->sx.centrox = macch->car.cx + (macch->car.width / 5) - 5;
            macch->dx.centrox = macch->car.cx + macch->car.width - (macch->car.width / 5) + 5;
            macch->sx.centroy = macch->car.cy + macch->car.height;
            macch->dx.centroy = macch->car.cy + macch->car.height;

            break;
        case 2:
            macch->sx.centrox = macch->car.cx + (macch->car.width / 5);
            macch->dx.centrox = macch->car.cx + macch->car.width - (macch->car.width / 5);
            macch->sx.centroy = macch->car.cy + macch->car.height;
            macch->dx.centroy = macch->car.cy + macch->car.height;
            break;
        case 3:
            macch->sx.centrox = macch->car.cx + (macch->car.width / 5) +5;
            macch->dx.centrox = macch->car.cx + macch->car.width - (macch->car.width / 5) - 5;
            macch->sx.centroy = macch->car.cy + macch->car.height;
            macch->dx.centroy = macch->car.cy + macch->car.height;
            break;

        default:
            break;
    }

    coca_try_finestrini(macch);
    coca_try_spoiler(macch);
    coca_try_tetto(macch);
}

string oselin_coca_to_svg(coca_device * macch){

    string svg;
    svg += coca_strg_carrozzeria(macch);
    svg += new_coca_strg_ruote(macch);
    svg += coca_strg_tetto(macch);
    svg += coca_strg_finestrini(macch);
    svg += coca_strg_spoiler(macch);
    return svg;
}

coca_device * oselin_coca_init(float param[6], float newx, float newy){
    coca_device * dev = new coca_device;

    float newparam [5];
    for (int i=0;i<3;i++) newparam[i] = param[i];
    newparam[3] = newx;
    newparam[4] = newy;

    oselin_coca_implementation(dev, newparam);
    return dev;
}

//MACHINE 


