#include <iostream>
#include <string>
#include "car_trailer.h"

#include <fstream>
#include <streambuf>
#include <sstream>
#include <signal.h>
using namespace std;


void displaymenu(){

}

void create(OselinDevice *dev, int n_args, char *param[]){

    float carlength, carheight, radius, svgwidth, svgheight;
    int ncars, nfloors;
    if (n_args > 0){
        svgwidth =  stof(param[2]);
        svgheight = stof(param[3]);
        carlength = stof(param[4]);
        carheight = stof(param[5]);
        radius =    stof(param[6]);
        ncars = atoi(param[7]);
        nfloors = atoi(param[8]);
    }
    else{
        displaymenu();
    }
    
    dev->param.svgwidth = svgwidth;
    dev->param.svgheight = svgheight;

    if (!oselin_init(dev, carlength, carheight, ncars, nfloors, radius)){
        oselin_trigonometry(dev);
    }
}

void load(OselinDevice *dev, int n_arg, char *param[], string path=""){
    string filename;
    if (n_arg > 0){
        filename = string(param[2]);
    }
    else filename = path;

    ifstream file(filename);
    stringstream buffer;
    buffer << file.rdbuf();
    string s = buffer.str();
    oselin_parsing(dev, s);
}

void help(){
    cout << "-h | --help\t\t allows you to read this awesome guide" << endl;
    cout << "-c | --create\t\t create a trailer SVG\t\t\t--create [SVG width] [SVG height] [Car length] [Car height] [Wheel radius] [Cars-per-trailer] [Floors]" << endl;
    cout << "-l | --load\t\t load SVG from file\t\t\t--load [path]" << endl;
    cout << "-i | --interface\t use graphic menu (for lame people)" << endl;
    
}


int main(int argc, char * argv[]) {

    OselinDevice *device = new OselinDevice;
    //signal(SIGINT,quit);
    if (argc==1){
        cout <<"Welcolme to the trailer-to-svg tool. Use '-h' to display commands.\n" << endl;
    }
    
    else{
        
        if      (string(argv[1]) == "-h" || string(argv[1]) == "--help"){
            help();//NO switch qua perché non si poteva fare l'enum
        }
        else if (string(argv[1]) == "-c" || string(argv[1]) == "--create"){
            if (argc < 9){
                cout << "Missing some parameters. Please check and try again." << endl;
            }
            else if (argc > 9){
                cout << "Too many parameters. Please check and try again." << endl;
            }
            else{
                create(device, argc,argv);
            }
        }
        else if (string(argv[1]) == "-l" || string(argv[1]) == "--load"){
            if (argc < 3){
                cout << "Missing some parameters. Please check and try again." << endl;
            }
            else if (argc > 3){
                cout << "Too many parameters. Please check and try again." << endl;
            }
            else{
                load(argv);
            }
        }
        else if (string(argv[1]) == "-i" || string(argv[1]) == "--interface"){
            cout << "interface" << endl;
        }
    
}


    return 0;
}

