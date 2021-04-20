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
    float svgwidth, svgheight, radius, carlength, carheight;
    int ncars = 0, height = 1; 
       
    //1-- 800
    cout << "SVG width: ";
    //cin >>  device->svgwidth;
    device->svgwidth = 800;
    //2-- 600
    cout << "SVG height: ";
    //cin >> device->svgheight;
    device->svgheight = 600;
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
    cin >>  radius;

    //6--
    cout << "Cars-per-trailer [1, 2]: ";
    cin >> ncars;

    //7--
    cout << "Number of floors [1, 2]: ";
    cin >> height;

    //CONSTRAINS:
    
    float margin = device->svgwidth/10;
    device->length = carlength * ncars + (ncars+1)*margin;
    device->height = carheight * height + 100;

    oselin_init(device, radius, carlength, carheight, ncars, height, margin);

    cout << device->svgwidth << endl;
    cout << device->svgheight << endl;
    oselin_trigonometry(device, radius);

    return oselin_to_svg(device, height);
}

void savesvg(string svg){
    if (svg != ""){
        ofstream MyFile("test.svg");
        MyFile << svg;
        MyFile.close();
        cout << "SAVED!\n" << endl;
    }
    else cout << "You must create or load a drawing before!\n" << endl;
}

void loadsvg(string filename){
    ifstream file(filename);
    stringstream buffer;
    buffer << file.rdbuf();
    string s = buffer.str();
    OselinDevice device = oselin_parsing(s);

    savesvg(oselin_to_svg(&device, 2));


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
            //cin >> temp;
            loadsvg("test.svg");
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

