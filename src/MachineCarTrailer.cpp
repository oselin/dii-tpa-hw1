#include "car_trailer.h"
#include <iostream>
#include <string>
#include <cmath>
#include "../TpaHomework1/include/Car.h"

using namespace std;

//bool are_equal(OselinMachine *, OselinMachine *);


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
            break;
        case 2:
            macch->sx.centrox = macch->car.cx + (macch->car.width / 5);
            macch->dx.centrox = macch->car.cx + macch->car.width - (macch->car.width / 5);
            break;
        case 3:
            macch->sx.centrox = macch->car.cx + (macch->car.width / 5) +5;
            macch->dx.centrox = macch->car.cx + macch->car.width - (macch->car.width / 5) - 5;
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
    svg += coca_strg_ruote(macch);
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


/*

dev->param.svgheight = 3 * dev->param.height;
        oselin_trigonometry(dev, false);

        dev->param.svgwidth = (ntrailers +1) * dev->abslength;
        dev->offset = 0.5 * dev->abslength;
        oselin_to_svg(dev);

        for (int i=1; i< ntrailers; i++){
            OselinDevice temp = (*dev);
            coca_device *car = new coca_device;

            temp.offset = (0.5 + i) * dev->abslength;

            float x = temp.offset + temp.param.margin;
            float y;

            float carparam[6] = {parameters[0],parameters[1], x, 0, parameters[2]};
            if (i==0) oselin_to_svg(&temp);
            else oselin_to_svg(&temp, false); 

            dev->svg += temp.svg + oselin_coca_svg(car,carparam);

            for (int i=1; i<= (int)parameters[4];i++){
                for (int j=0; j <= (int)parameters[5];j++){
                    carparam[2] += 2 * temp.param.margin + (i-1)*carparam[0];   
                    carparam[3] = (j-1)*temp.downfloor.height + temp.absy - 3 * temp.downfloor.height;
                    dev->svg += temp.svg + oselin_coca_svg(car, carparam);

                }           

            }
        }

        save(dev, 1);
        exit(0);
    }
*/