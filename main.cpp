#include <iostream>
#include <string>
#include "car_trailer.h"

#include <fstream>
#include <streambuf>
#include <sstream>
using namespace std;

char menu(){
    string com; char inp;
    
    com += "Welcome to the SVG TRAILER CREATOR\n";
    com += "----------------------------------\n";
    com += "Here's what you can do:\n";
    com += "[l] - load SVG drawing from file\n";
    com += "[c] - create a new trailer\n";
    com += "[s] - save SVG draving to file\n";
    com += "[e] - exit";
    com += "\n\n";
    com += "What do you want to do?: ";

    cout << com << endl;
    cin >> inp;
    return inp;

}

string createsvg(OselinDevice *device){
    /**
     * CHOSEN PARAEMTERS:
     * @param SVG WIDTH
     * @param SVG HEIGHT
     * @param WHEEL'S RADIUS -> 16" 17" 18"
     * @param CAR-PER-TRAILER ->1 OR 2 PER TRAILER
     * @param HEIGHT -> 1 OR 2 FLOORS
     * @param CAR'S LENGTH -> TRAILER LENGTH = CAR-PER-TRAILER * CAR'S LENGTH
     * @param CAR'S HEIGHT -> TRAILER HEIGHT = CAR'S HEIGHT * HEIGHT
     * */
    float  carlength, carheight;
    int ncars = 0; 
       
    //1-- 800
    cout << "SVG width: ";
    //cin >>  device->svgwidth;
    device->param.svgwidth = 800;
    //2-- 600
    cout << "SVG height: ";
    //cin >> device->svgheight;
    device->param.svgheight = 600;
    //3--
    cout << "CAR LENGTH: ";
    //cin >>  carlength;
    carlength = 200;
    //4--
    cout << "CAR HEIGHT: ";
    //cin >>  carheight;
    carheight = 100;
    //5--
    cout << "WHEEL RADIUS [16, 17, 18]: ";
    cin >>  device->param.radius;

    //6--
    cout << "Cars-per-trailer [1, 2]: ";
    cin >> ncars;

    //7--
    cout << "Number of floors [1, 2]: ";
    cin >> device->param.nfloors;

    //CONSTRAINS:
    
    float margin = device->param.svgwidth/10;
    device->length = carlength * ncars + (ncars+1)*margin;
    device->height = carheight * device->param.nfloors + 100;

    oselin_init(device, carlength, carheight, ncars, margin);

    cout << device->param.svgwidth << endl;
    cout << device->param.svgheight << endl;
    oselin_trigonometry(device);

    return oselin_to_svg(device);
}

void savesvg(string svg){
    if (svg != ""){
        string filename;
        cout << "File name for saving (with extension): ";
        cin >> filename;
        ofstream MyFile(filename);
        MyFile << svg;
        MyFile.close();
        cout << "SAVED!\n" << endl;
    }
    else cout << "You must create or load a drawing before!\n" << endl;
}

void loadsvg(OselinDevice *dev, string filename){
    ifstream file(filename);
    stringstream buffer;
    buffer << file.rdbuf();
    string s = buffer.str();
    cout << "1" <<endl;
    oselin_parsing(dev, s);
}

int main() {

    OselinDevice *device = new OselinDevice;
    string svg;
    char a = menu();
    while (a != 'e'){
        switch (a)
        {
        case 'l':       //LOADING FROM FILE
        {            
            string temp;
            cout << "path/filename: ";
            cin >> temp;
            loadsvg(device, temp);
            svg = oselin_to_svg(device);
            break;
        }
        case 'c':       //CREATING AN SVG
            svg = createsvg(device);
            break;
        case 's':       //SAVING TO FILE
            savesvg(svg);
            break;
        default:
            break;
        }
        a = menu();
    }

    return 0;
}

