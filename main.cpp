#include <iostream>
#include <string>
#include "car_trailer.h"
#include "Car.h"
#include "machine_car_trailer.h"

#include <fstream>
#include <streambuf>
#include <sstream>
using namespace std;

string questions[] = {"SVG width: ", "SVG height: ","Car lenght: ","Car height: ", "Wheel radius [16,17,18]: ","Cars-per-trailer [1,2]: ","Number of floors [1,2]: "};


void displaymenu(){
    string com = "";
    com += "----------------------------------\n";
    com += "Here's what you can do:\n";
    com += "[1] - load SVG drawing from file\n";
    com += "[2] - create a new trailer\n";
    com += "[3] - save SVG drawing to file\n";
    com += "[4] - change a parameter\n";
    com += "[5] - create a machine\n";
    com += "[6] - exit";

    cout << com << endl;

}

void help(){
    cout << "-h | --help\t\t allows you to read this awesome guide" << endl;
    cout << "-c | --create\t\t create a trailer SVG\t\t\t--create [SVG width] [SVG height] [Car length] [Car height] [Wheel radius] [Cars-per-trailer] [Floors]" << endl;
    cout << "-l | --load\t\t load SVG from file\t\t\t--load [path]" << endl;
    cout << "-m | --machine\t\t draw a train of trailers\t\t " << endl;
    cout << "-i | --interface\t use graphic menu (for lame people)" << endl;
    
}

/**
 * Load OselinDevice from file. It can work with graphical menu or inline commands
 **/
string load(OselinDevice *dev, int n_args = 0, char *param[] = NULL){
    string filename;
    if (n_args != 0){
        filename = string(param[2]);
    }
    else{
        cout << "path/file [with extension]: ";
        cin >> filename;
    }
    try{
        ifstream file(filename);
        stringstream buffer;
        buffer << file.rdbuf();
        string s = buffer.str();
        oselin_parsing(dev, s);
        return "loaded successfully";
    }
    catch(const std::exception& e){
        return "Somethig went wrong. The file exists?";
    }
}

/**
 * Create OselinDevice from scratch. It can work with graphical menu or inline commands
 **/
string create(OselinDevice *dev, int n_args = 0, char *param[] = NULL){

    float parameters[5];
    Parameters p;
    if (n_args != 0){
        try
        {
            p.svgwidth  = stof(param[2]);
            p.svgheight = stof(param[3]);

           
            p.length    = stof(param[4]);
            p.height    = stof(param[5]);
            p.radius    = stof(param[6]);
            p.ncars     = atoi(param[7]);
            p.nfloors   = atoi(param[8]);
            //p.margin;

            //for (int i=0;i<5;i++) parameters[i] = stof(param[i+4]);
        }
        catch(const exception& e)
        {
            cout << errors(8) << endl;
            exit(1);
        }
        
        
    }
    else{
        try{
            for (int i=0; i<7; i++){
                cout << questions[i];
                if (i==0) cin >> p.svgwidth;
                else if (i==1) cin >> p.svgheight;
                else cin >> parameters[i-2];
            }}
        catch(const exception& e){
            return errors(8);

        }

        p.length    = parameters[0];
        p.height    = parameters[1];
        p.radius    = parameters[2];
        p.ncars     = (int)parameters[3];
        p.nfloors   = (int)parameters[4];
        //p.margin;
    }
    
    (*dev) = (*oselin_init(p));
    if (dev!=NULL){
        oselin_trigonometry(dev);
        return "Created successfully";
    }
    return "Something went wrong";
}

/**
 * Save an existing OselinDevice to file
 **/
string save(OselinDevice *dev, int mode = 0){
    char resp;
    int saving = 0;
    if (!mode){
        cout << "Do you want measures on the drawing?[y/n] ";
        cin >> resp;
        if (resp == 'y' || resp == 'Y') {
            oselin_to_svg(dev, true, true);
            ++saving ;
        }
        else if (resp == 'n' || resp == 'N'){
            oselin_to_svg(dev);
            ++saving ;
        }
        
    }
    else ++saving;
    if (saving){
        string filename;
        cout << "File name for saving (with extension): ";
        cin >> filename;
        ofstream MyFile(filename);
        MyFile << (dev->svg + "\n</svg>");
        MyFile.close();
        return "SAVED!";
    }
    return "Aborting...";
}

/**
 * Change some parameters of an existing OselinDevice
 **/
string change(OselinDevice *dev){

    int choice; float newvalue;
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
        if (oselin_set(dev,choice, newvalue) != NULL) {
            (*dev) = (*oselin_set(dev,choice, newvalue));
            return "changed successfully";
        }
    }
    return "Aborting...";
}

/**
 * Just display some possible commands
 **/
void machine_displaymenu(){
    string com = "";
    com += "----------------------------------\n";
    com += "Here's what you can do:\n";
    com += "[1] - load machine SVG drawing from file\n";
    com += "[2] - create a new machine\n";
    com += "[3] - save machine SVG drawing to file\n";
    com += "[4] - change a parameter\n";
    com += "[5] - return";

    cout << com << endl;

}

/**
 * Create a new machine from scratch
 **/
string machine_create(OselinDevice *dev, OselinMachine *mach){
    //PARAM
    //lenght | height | radius | ncars | nfloors | ntrailers
    
    int ntrailers;
    float parameters[5];
    for (int i=0; i<5; i++){
        cout << questions[i+2];
        cin >> parameters[i];
    }
    cout << "How many trailers? ";
    cin >> ntrailers;
    Parameters p;
    p.length    = parameters[0];
    p.height    = parameters[1];
    p.radius    = parameters[2];
    p.ncars     = (int)parameters[3];
    p.nfloors   = (int)parameters[4];

    mach->trailerarray = new OselinDevice* [ntrailers];        
    mach->cararray = new coca_device* [p.nfloors * p.ncars *ntrailers];

    (*mach) = (*oselin_machine_init(p, ntrailers));
    if (mach!=NULL) return "Machine created successfully.";
    return "An error occurred.";
}

/**
 * Change parameters of an existing machine
 **/
string machine_change(OselinDevice *dev, OselinMachine *mach){
    if (mach->parameters.length != 0){
        int choice; float newvalue;
        Parameters p = mach->parameters;
        string help = "Choose what to change:\n";
        help += "[0] Set new car length\n";
        help += "[1] Set new car height\n";
        help += "[2] Set new radius\n";
        help += "[3] Set new number of cars per trailer\n";
        help += "[4] Set new number of floors\n";
        help += "[5] Set new number of trailers\n";

        cout << help << endl;
        cout << "Your choice: ";
        cin >> choice;
        cout << "New value: ";
        cin >> newvalue;

        if (choice > -1 || choice < 6){
            if (choice == 5) mach->length = (int)newvalue;
            //else array[choice] = newvalue;
            //(*mach) = (*oselin_machine_init(dev, mach->length, array));
            return "Machine updated.";
        }
        return "Aborting.";
    }
    return "The machine looks empty. Did you created one first?";
    
}

/**
 * Load a machine from file
 **/
string machine_load(OselinMachine *mach){
    string filename;
    cout << "path/file [with extension]: ";
    cin >> filename;
    

    ifstream file(filename);
    stringstream buffer;
    buffer << file.rdbuf();
    string s = buffer.str();
    oselin_machine_parsing(mach, s);
    return "al";
}

/**
 * Sub loop for working in a machine environment
 **/
void machine_mainloop(OselinDevice *dev, OselinMachine *mach){

    int inloop = 1, ntrailers;
    string message;
    float f[5];
    cout << "MACHINE MODE" << endl;
    do{
        
        machine_displaymenu();
        char choice;
        cout << "Your choice: " ;
        cin >> choice;

        switch (choice)
        {
        case '1':
            //message = machine_load(mach);
            message = "This feature will come soon.";
            break;
        case '2':
            message = machine_create(dev, mach);
            
            break;
        case '3':
            message = oselin_machine_save(mach);
            break;    
        case '4':
            message = machine_change(dev,mach);
            break;
        case '5':
            inloop = 0;
            message = "Closing.";
            break;
        default:
            message = "Command not found.";
            break;
        }
        system("clear");
        cout << message << " What's next?" << endl;
    }while(inloop);

}

/**
 * Main loop of the program
 **/
void mainloop(OselinDevice *dev, OselinMachine *mach){

    int inloop = 1;
    string message;
    cout << "Welcome to the SVG TRAILER CREATOR" << endl;
    do{
        displaymenu();
        char choice;
        cout << "Your choice: " ;
        cin >> choice;

        switch (choice)
        {
        case '1':
            message = load(dev);
            break;
        case '2':
            message = create(dev);
            break;
        case '3':
            message = save(dev);
            break;    
        case '4':
            message = change(dev);
            break;
        case '5':
            machine_mainloop(dev, mach);
            message = "";
        case '6':
            inloop = 0;
            break;
        default:
            cout << "Command not found." << endl;
            break;
        }
        system("clear");
        cout << message << " What's next?" << endl;
    }while(inloop);

}

int main(int argc, char * argv[]) {

    OselinDevice *device = new OselinDevice;
    
    OselinMachine *mach = new OselinMachine;
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
                cout << create(device, argc,argv) << endl;;
                mainloop(device, mach);
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
                cout << load(device, argc,argv) << endl;
                mainloop(device, mach);
            }
        }
        else if (string(argv[1]) == "-m" || string(argv[1]) == "--machine"){
            machine_mainloop(device, mach);
            mainloop(device, mach);
        }
        else if (string(argv[1]) == "-i" || string(argv[1]) == "--interface"){
            mainloop(device, mach);
        }
    }
    return 0;
}

