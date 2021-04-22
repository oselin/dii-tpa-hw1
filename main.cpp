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

float questionloop(string question, int questiontype){
    float myvar = 0;
    switch (questiontype)
    {
    case 1:
        while ((myvar != 16)  && (myvar != 17) && (myvar != 18)){
            cout << question;
            cin >> myvar;
        }
        break;
    case 2:
        while (myvar != 1 && myvar != 2){
            cout << question;
            cin >> myvar;
        }
        break;
    
    default:
        while (myvar<=0){
            cout << question;
            cin >> myvar;
        }
        break;
    }
    return myvar;
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
    device->param.svgwidth = questionloop("SVG width: ", 0);
    device->param.svgheight = questionloop("SVG height: ", 0);
    carlength = questionloop("Car lenght: ", 0);
    carheight = questionloop("Car height: ", 0);
    device->param.radius = questionloop("Wheel radius [16,17,18]: ", 1);
    ncars = static_cast<int>(questionloop("Cars-per-trailer [1,2]: ", 2));
    device->param.nfloors = questionloop("Number of floors [1,2]: ", 2);

    //CONSTRAINS:
    
    float margin = device->param.svgwidth/10;
    device->length = carlength * ncars + (ncars+1)*margin;
    device->height = carheight * device->param.nfloors + 100;
    if (oselin_init(device, carlength, carheight, ncars)){
        oselin_trigonometry(device);
        return oselin_to_svg(device);
    }
    
    return "";

    
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
    else errors(3);
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

