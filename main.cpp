#include <iostream>
#include <string>
#include "car_trailer.h"

#include <fstream>
#include <streambuf>
#include <sstream>
#include <signal.h>
using namespace std;


void displaymenu(){
    string com = "Welcome to the SVG TRAILER CREATOR\n";
    com += "----------------------------------\n";
    com += "Here's what you can do:\n";
    com += "[1] - load SVG drawing from file\n";
    com += "[2] - create a new trailer\n";
    com += "[3] - save SVG draving to file\n";
    com += "[4] - change a parameter\n";
    com += "[5] - create a machine\n";
    com += "[6] - exit";

    cout << com << endl;

}

void help(){
    cout << "-h | --help\t\t allows you to read this awesome guide" << endl;
    cout << "-c | --create\t\t create a trailer SVG\t\t\t--create [SVG width] [SVG height] [Car length] [Car height] [Wheel radius] [Cars-per-trailer] [Floors]" << endl;
    cout << "-l | --load\t\t load SVG from file\t\t\t--load [path]" << endl;
    cout << "-m | --machine\t\t draw a train of trailers\t\t--machine [Number of trailers]" << endl;
    cout << "-i | --interface\t use graphic menu (for lame people)" << endl;
    
}

void load(OselinDevice *dev, int n_arg = 0, char *param[] = NULL){
    string filename;
    if (n_arg != 0){
        filename = string(param[2]);
    }
    else{
        cout << "path/file [with extension]: ";
        cin >> filename;
    }

    ifstream file(filename);
    stringstream buffer;
    buffer << file.rdbuf();
    string s = buffer.str();
    oselin_parsing(dev, s);
}

void create(OselinDevice *dev, int n_args = 0, char *param[] = NULL){

    float parameters[5];
    string questions[] = {"SVG width: ", "SVG height: ","Car lenght: ","Car height: ", "Wheel radius [16,17,18]: ","Cars-per-trailer [1,2]: ","Number of floors [1,2]: "};

    if (n_args != 0){
        for (int i=0;i<5;i++) parameters[i] = stof(param[i+2]);
    }
    else{
        for (int i=0; i<7; i++){
            cout << questions[i] << endl;
            if (i==0) cin >> dev->param.svgwidth;
            else if (i==1) cin >> dev->param.svgheight;
            else cin >> parameters[i];
        }
    }
    
    if (!oselin_init(dev, parameters)){
        oselin_trigonometry(dev);
    }
}

void save(OselinDevice *dev){
    if (dev->svg != ""){
        string filename;
        cout << "File name for saving (with extension): ";
        cin >> filename;
        ofstream MyFile(filename);
        MyFile << (dev->svg + "\n</svg>");
        MyFile.close();
        cout << "SAVED!\n" << endl;
    }
}

void change(OselinDevice *dev){

    int choice; float newvalue;
    float array [] = {-1,-1,-1,-1,-1};
    string help = "Choose what to change:\n";
    help += "[0] Set new car length\n";
    help += "[1] Set new car height\n";
    help += "[2] Set new radius\n";
    help += "[3] Set new number of cars per trailer\n";
    help += "[4] Set new number of floors\n";

    cout << help << endl;
    cout << "Your choice: ";
    cin >> choice;
    cout << "New value: ";
    cin >> newvalue;

    if (choice > -1 || choice < 5){
        array[choice] = newvalue;
        oselin_set(dev,array);
    }
    else cout << "Aborting..." << endl;
}

void machine(OselinDevice *dev){

}

void mainloop(OselinDevice *dev){

    int inloop = 1, choice;
    do{
        displaymenu();

        cout << "Your choice: " ;
        cin >> choice;

        switch (choice)
        {
        case 1:
            load(dev);
            break;
        case 2:
            create(dev,0);
            break;
        case 3:
            save(dev);
            break;    
        case 4:
            change(dev);
            break;
        case 5:
            machine(dev);
        case 6:
            inloop = 0;
        default:
            break;
        }
    }while(inloop);

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
                load(device, argc,argv);
            }
        }
        else if (string(argv[1]) == "-m" || string(argv[1]) == "--machine"){
            if (argc < 3){
                cout << "Missing some parameters. Please check and try again." << endl;
            }
            else if (argc > 3){
                cout << "Too many parameters. Please check and try again." << endl;
            }
            else{
                load(device, argc,argv);
            }
        }
        else if (string(argv[1]) == "-i" || string(argv[1]) == "--interface"){
            mainloop(device);
        }
    
}


    return 0;
}

