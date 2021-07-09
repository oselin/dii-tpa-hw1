#include <iostream>
#include <string>
#include "car_trailer.h"
#include "machine_car_trailer.h"

#include <fstream>
#include <streambuf>
#include <sstream>

#include <unordered_map>
using namespace std;

string questions[] = {"SVG width: ", "SVG height: ","Car lenght: ","Car height: ", "Wheel radius [16,17,18]: ","Cars-per-trailer [1,2]: ","Number of floors [1,2]: "};

void print(unordered_map<string,float> umap){
    for (pair<string, float> p : umap){
        cout << p.first << " | " << p.second << endl;
    }
}

void displaymenu(){
    string com = "";
    com += "----------------------------------------\n";
    com += "Here's what you can do:\n";
    com += "[1] - load SVG drawing from file\n";
    com += "[2] - create a new trailer\n";
    com += "[3] - save SVG drawing to file\n";
    com += "[4] - change a parameter\n";
    com += "[5] - create a machine\n";
    com += "[6] - create a machine from this trailer\n";
    com += "[7] - display Device Data\n";
    com += "[8] - display Machine Data\n";
    com += "[9] - exit";

    cout << com << endl;

}

void help(){
    cout << "-h | --help\t\t allows you to read this awesome guide" << endl;
    cout << "-c | --create\t\t create a trailer SVG\t\t\t--create [SVG width] [SVG height] [Car length] [Car height] [Wheel radius] [Cars-per-trailer] [Floors]" << endl;
    cout << "-l | --load\t\t load SVG from file\t\t\t--load [path]" << endl;
    cout << "-m | --machine\t\t draw a train of trailers\t\t " << endl;
    cout << "-i | --interface\t use graphic menu (for lame people)" << endl;
    
}

void machine_displaymenu(){
    string com = "";
    com += "--------------MACHINE MODE--------------\n";
    com += "----------------------------------------\n";
    com += "Here's what you can do:\n";
    com += "[1] - load machine SVG drawing from file\n";
    com += "[2] - create a new machine\n";
    com += "[3] - save machine SVG drawing to file\n";
    com += "[4] - change a parameter\n";
    com += "[5] - display Machine Data\n";
    com += "[6] - return";

    cout << com << endl;

}

unordered_map<string, float> argv2umap(char * argv[]){
    if (argv != NULL){
        unordered_map<string,float> umap;
        try{
            umap["svg_width"] =  stof(argv[2]);
            umap["svg_height"] = stof(argv[3]);
            umap["car_length"] = stof(argv[4]);
            umap["car_height"] = stof(argv[5]);
            umap["car_radius"] = stof(argv[6]);
            umap["n_cars"] =     stof(argv[7]);
            umap["n_floors"] =   stof(argv[8]);
        }catch (const exception &e){
            throw e;
        }

        return umap;
    }

    throw std::invalid_argument("Something went wrong.");
}

oselin::Trailer* load(int argc = 0, char *argv[] = NULL){
    string s, filename;
    if (argv != NULL && argc >=2){
        filename = string(argv[2]);
    }
    else{
        cout << "path/file [with extension]: ";
        cin >> filename;
    }
    try{
        ifstream file(filename);
        stringstream buffer;
        buffer << file.rdbuf();
        s = buffer.str();
    }
    catch(const exception& e){
        cout << "An error occurred here" << endl;
        throw e;
    }
    oselin::Trailer *t = new oselin::Trailer(s);
    return t;
}

oselin::Trailer* create(oselin::Trailer *trailer){
    
    if (trailer->isempty()){
        oselin::Parameters p;
        try{
            float answ;
            for (int i=0; i<7; i++){
                cout << questions[i];
                cin >> answ;
                switch (i)
                {
                case 0:
                    p.svg_width(answ);
                    break;
                case 1:
                    p.svg_height(answ);
                    break;
                case 2:
                    p.car_length(answ);
                    break;
                case 3:
                    p.car_height(answ);
                    break;
                case 4:
                    p.car_radius(answ);
                    break;
                case 5:
                    p.n_cars(answ);
                    break;
                case 6:
                    p.n_floors(answ);
                    break;
                default:
                    throw out_of_range("An error occurred.");
                }}
        }catch(const exception& e){
            throw e;
        }
        //Prevent data loss if something goes wrong
        p.isempty(false);
        oselin::Trailer *t = new oselin::Trailer(p, 0);
        return t;
    }
    return trailer;    

}

string save(oselin::Trailer *trailer, int mode=0){
    char resp;
    string svg;
    if (!mode){
        cout << "Do you want measures on the drawing?[y/n] ";
        cin >> resp;
        if (resp == 'y' || resp == 'Y') {
            svg = trailer->svg(true, true);
        }
        else if (resp == 'n' || resp == 'N'){
            svg = trailer->svg(true);
        }
        
    }
    else svg = trailer->svg();
    string filename;
    cout << "File name for saving (with extension): ";
    cin >> filename;
    ofstream MyFile(filename);
    MyFile << (svg + "\n</svg>");
    MyFile.close();
    return "SAVED!";
}

string change(oselin::Trailer *trailer){
    if (trailer->isempty()) return "You might not have initialized a device. Aborting";
    int choice; float newvalue;
    system("clear");
    string help = "Choose what to change:\n";
    help += "[0] Set new car SVG width\n";
    help += "[1] Set new car SVG height\n";
    help += "[2] Set new car length\n";
    help += "[3] Set new car height\n";
    help += "[4] Set new radius\n";
    help += "[5] Set new number of cars per trailer\n";
    help += "[6] Set new number of floors\n";
    help += "--- Any other number to go back\n";

    cout << help << endl;
    cout << "Your choice: ";
    cin >> choice;

    if (choice >7 || choice <0) return "Aborting.";
    cout << "New value: ";
    cin >> newvalue;

    switch (choice)
    {
    case 0: trailer->svg_width(newvalue); 
    case 1: trailer->svg_height(newvalue);
    case 2: trailer->car_length(newvalue);
    case 3: trailer->car_height(newvalue);
    case 4: trailer->car_radius(newvalue);
    case 5: trailer->n_cars(newvalue);    
    case 6: trailer->n_floors(newvalue);  
    default:
        break;
    }
    return "Parameter has been changed";
}

void machine_save(oselin::Machine *machine){
    if (machine != NULL){
        if (machine->isempty() == 0){
            string filename, svgmach;
            cout << "File name for saving (with extension): ";
            cin >> filename;
            ofstream MyFile(filename);
            svgmach =  machine->svg();
            if (svgmach == "") throw range_error("Something went wrong.");
            else{
                MyFile << (svgmach + "\n</svg>");
                MyFile.close();
                cout << "Saved." << endl;
            }
        }
    }
    else throw logic_error("Pointer is null.");
    
}

oselin::Machine * convertFromTrailer(oselin::Trailer *trailer){
    oselin::Machine *machine = new oselin::Machine(); //worst case: return a brand new machine
    if (!trailer->isempty()){
        int ntrailers;
        cout << "How many trailers? ";
        cin >> ntrailers;
        if (ntrailers > 0){
            machine = new oselin::Machine(trailer, ntrailers);
        }
    }
    return machine;
}

oselin::Machine * machine_create(){

    int ntrailers;
    float parameters[5];
    for (int i=0; i<5; i++){
        cout << questions[i+2];
        cin >> parameters[i];
    }
    cout << "How many trailers? ";
    cin >> ntrailers;
    oselin::Parameters p;
    p.car_length(parameters[0]);
    p.car_height(parameters[1]);
    p.car_radius(parameters[2]);
    p.n_cars    (parameters[3]);
    p.n_floors  (parameters[4]);

    oselin::Machine *m = new oselin::Machine(p, ntrailers);
    return m;
}

oselin::Machine * machine_load(){
    string filename;
    cout << "path/file [with extension]: ";
    cin >> filename;
    
    oselin::Machine *m;
    try{
        ifstream file(filename);
        stringstream buffer;
        buffer << file.rdbuf();
        string s = buffer.str();
        m = new oselin::Machine(s);
    }catch(exception &e){throw invalid_argument("The file does not exist.");}

    return m;
}

/**
 * Sub loop for working in a machine environment
 **/
oselin::Machine * machine_mainloop(oselin::Machine *mach){
    system("clear");
    int inloop = 1, ntrailers;
    string message;
    float f[5];

    oselin::Machine *machine = new oselin::Machine(mach);
    do{
        
        machine_displaymenu();
        char choice;
        cout << "Your choice: " ;
        cin >> choice;

        switch (choice)
        {
        case '1':
            machine = machine_load();
            message = "Machine loaded successfully.";
            cout << machine << endl;
            break;
        case '2':
            machine = machine_create();
            message = "Machine created successfully.";
            cout << machine << endl;
            
            break;
        case '3':
            machine_save(machine);
            break;    
        case '4':
            //message = machine_change(dev,mach);
            break;
        case '5':
            system("clear");
            cout << machine << endl;
            getchar();getchar();
            break;
        case '6':
            inloop = 0;
            break;
        default:
            message = "Command not found.";
            break;
        }
        system("clear");
        if (inloop) cout << message << " What's next?" << endl;
    }while(inloop);
    
    return machine;
}


void mainloop(oselin::Trailer *trailer, oselin::Machine *machine){

    
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
            trailer = load();
            message = "File loaded successfully.";
            break;
        case '2':
            trailer->isempty(true);
            trailer = create(trailer);
            message = "Created successfully.";
            break;
        case '3':
            message = save(trailer);
            break;    
        case '4':
            message = change(trailer);
            break;
        case '5':
            machine = machine_mainloop(machine);
            message = "";
            break;
        case '6':
            machine = convertFromTrailer(trailer);
            break;
        case '7':
            system("clear");
            cout << trailer;
            getchar(); getchar();
            break;
        case '8':
            system("clear");
            cout << machine;
            getchar(); getchar();
            break;
        case '9':
            inloop = 0;
            break;
        default:
            cout << "Command not found." << endl;
            break;
        }
        system("clear");
        if (inloop) cout << message << " What's next?" << endl;

    }while(inloop);

}


int main(int argc, char * argv[]) {

    oselin::Trailer *trailer = new oselin::Trailer();
    oselin::Machine *machine = new oselin::Machine();
    
    if (argc==1){
        cout << "Welcolme to the trailer-to-svg tool. Use '-h' to display commands.\n" << endl;
    }
    else{
        
        if      (string(argv[1]) == "-h" || string(argv[1]) == "--help") help();
        else if (string(argv[1]) == "-c" || string(argv[1]) == "--create"){
            if (argc < 9){
                cout << "Missing some parameters. Please check and try again." << endl;
            }
            else if (argc > 9){
                cout << "Too many parameters. Please check and try again." << endl;
            }
            else{
                
                trailer = new oselin::Trailer(oselin::Parameters(argv),0);
                cout << "Trailer created successfully." << endl;
                mainloop(trailer, machine);
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
                trailer = load(argc,argv);
                cout << "Trailer loaded successfully." << endl;
                mainloop(trailer, machine);
            }
        }
        else if (string(argv[1]) == "-m" || string(argv[1]) == "--machine"){;
            machine = machine_mainloop(machine);
            mainloop(trailer, machine);
        }
        else if (string(argv[1]) == "-i" || string(argv[1]) == "--interface"){
            mainloop(trailer, machine);
        }
    }

    delete trailer;
    delete machine;

    return 0;
}

