#include <iostream>
#include <string>
#include "car_trailer.h"

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

oselin::Trailer* load(char *argv[] = NULL){
    string filename;
    if (argv != NULL){
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
    }
    catch(const exception& e){
        throw e;
    }

    oselin::Trailer *t = new oselin::Trailer(s);
    return t;
}
oselin::Trailer* create(unordered_map<string, float> parameters){
    
    if (parameters.size() == 0){
        try{
            for (int i=0; i<7; i++){
                cout << questions[i];
                switch (i)
                {
                case 0:
                    cin >> parameters["svg_width"];
                    break;
                case 1:
                    cin >> parameters["svg_height"];
                    break;
                case 2:
                    cin >> parameters["car_length"];
                    break;
                case 3:
                    cin >> parameters["car_height"];
                    break;
                case 4:
                    cin >> parameters["car_radius"];
                    break;
                case 5:
                    cin >> parameters["n_cars"];
                    break;
                case 6:
                    cin >> parameters["n_floors"];
                    break;
                default:
                    throw out_of_range("An error occurred.");
                }}
        }catch(const exception& e){
            throw e;
        }}

    oselin::Trailer *t = new oselin::Trailer(parameters);
    return t;

}
string save(oselin::Trailer *trailer){
    char resp;
    int saving = 0;
    string svg;
    if (!mode){
        cout << "Do you want measures on the drawing?[y/n] ";
        cin >> resp;
        if (resp == 'y' || resp == 'Y') {
            svg = trailer->svg(true, true);
            ++saving ;
        }
        else if (resp == 'n' || resp == 'N'){
            tsvg = trailer->svg();
            ++saving ;
        }
        
    }
    else ++saving;
    if (saving){
        string filename;
        cout << "File name for saving (with extension): ";
        cin >> filename;
        ofstream MyFile(filename);
        MyFile << (svg + "\n</svg>");
        MyFile.close();
        return "SAVED!";
    }
    return "Aborting...";
}

string change(oselin::Trailer *trailer){

    int choice; float newvalue;
    string help = "Choose what to change:\n";
    help += "[0] Set new car SVG width\n";
    help += "[1] Set new car SVG height\n";
    help += "[2] Set new car length\n";
    help += "[3] Set new car height\n";
    help += "[4] Set new radius\n";
    help += "[5] Set new number of cars per trailer\n";
    help += "[6] Set new number of floors\n";

    cout << help << endl;
    cout << "Your choice: ";
    cin >> choice;
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
    return "Aborting...";
}


void mainloop(oselin::Trailer *trailer, oselin::Machine *machine, unordered_map<string, float> &parameters){

    
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
            message = load(trailer);
            break;
        case '2':
            parameters.clear();
            trailer = create(parameters);
            print(trailer->parameters());
            message = "Created successfully";
            break;
        case '3':
            message = save(trailer);
            break;    
        case '4':
            message = change(trailer);
            break;
        case '5':
            //machine_mainloop(dev, mach);
            message = "";
        case '6':
            inloop = 0;
            break;
        default:
            cout << "Command not found." << endl;
            break;
        }
        //system("clear");
        cout << message << " What's next?" << endl;

    }while(inloop);

}

/**
 * Sub loop for working in a machine environment
 **/
int main(int argc, char * argv[]) {

    oselin::Trailer *trailer;
    oselin::Machine *machine;
    unordered_map<string, float> parameters;
    
    if (argc==1){
        cout <<"Welcolme to the trailer-to-svg tool. Use '-h' to display commands.\n" << endl;
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
                parameters = argv2umap(argv);
                trailer = create(parameters);
                mainloop(trailer, machine, parameters);
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
                //cout << load(trailer, argc,argv) << endl;
                mainloop(trailer, machine, parameters);
            }
        }
        else if (string(argv[1]) == "-m" || string(argv[1]) == "--machine"){
            ///machine_mainloop(device, mach);
            mainloop(trailer, machine, parameters);
        }
        else if (string(argv[1]) == "-i" || string(argv[1]) == "--interface"){
            mainloop(trailer, machine, parameters);
        }
    }

    return 0;
}

