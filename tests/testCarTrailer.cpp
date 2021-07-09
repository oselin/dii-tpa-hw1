#include "car_trailer.h"
#include "catch2/catch2.hpp"
#include <fstream>
#include <streambuf>
#include <sstream>
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;
TEST_CASE("Constructor should throw as svg-width is zero", "[Trailer]") {

    oselin::Parameters p;
    p.svg_width(0);
    p.svg_height(600);
    p.car_radius(17);
    p.car_length(150);
    p.car_height(50);
    p.n_cars(2);
    p.n_floors(2);
    
    REQUIRE_THROWS_AS(oselin::Trailer(p,0), invalid_argument);
}

TEST_CASE("Constructor should throw as svg-height is zero", "[Trailer]") {

    oselin::Parameters p;
    p.svg_width(800);
    p.svg_height(-200);
    p.car_radius(17);
    p.car_length(150);
    p.car_height(50);
    p.n_cars(2);
    p.n_floors(2);
    
    REQUIRE_THROWS_AS(oselin::Trailer(p,0), invalid_argument);
}


TEST_CASE("Constructor should throw as car_length is too much", "[Trailer]") {

    oselin::Parameters p;
    p.svg_width(800);
    p.svg_height(600);
    p.car_radius(17);
    p.car_length(2000);
    p.car_height(50);
    p.n_cars(2);
    p.n_floors(2);
    
    REQUIRE_THROWS_AS(oselin::Trailer(p,0), invalid_argument);
}


TEST_CASE("Constructor should throw as cars are too many", "[Trailer]") {

    oselin::Parameters p;
    p.svg_width(8000);
    p.svg_height(600);
    p.car_radius(17);
    p.car_length(150);
    p.car_height(50);
    p.n_cars(4);
    p.n_floors(2);
    
    REQUIRE_THROWS_AS(oselin::Trailer(p,0), out_of_range);
}


TEST_CASE("Constructor should throw as floors are too many", "[Trailer]") {

    oselin::Parameters p;
    p.svg_width(8000);
    p.svg_height(600);
    p.car_radius(17);
    p.car_length(150);
    p.car_height(50);
    p.n_cars(2);
    p.n_floors(6);
    
    REQUIRE_THROWS_AS(oselin::Trailer(p,0), out_of_range);
}

TEST_CASE("Constructor should throw as cars are too short", "[Trailer]") {

    oselin::Parameters p;
    p.svg_width(800);
    p.svg_height(600);
    p.car_radius(17);
    p.car_length(20);
    p.car_height(50);
    p.n_cars(2);
    p.n_floors(2);
    
    REQUIRE_THROWS_AS(oselin::Trailer(p,0), invalid_argument);
}


TEST_CASE("Constructor should throw as structural error", "[Trailer]") {

    oselin::Parameters p;


    p.svg_width(800);
    p.svg_height(600);
    p.car_radius(17);
    p.car_length(150);
    p.car_height(50);
    p.n_cars(1);
    p.n_floors(2);
    REQUIRE_THROWS_AS(oselin::Trailer(p), invalid_argument);
}
TEST_CASE("Constructor should throw as radius error", "[Trailer]") {

    oselin::Parameters p;
    p.svg_width(800);
    p.svg_height(600);
    p.car_radius(2);
    p.car_length(150);
    p.car_height(50);
    p.n_cars(1);
    p.n_floors(2);
    REQUIRE_THROWS_AS(oselin::Trailer(p,0), out_of_range);
}


TEST_CASE("Constructor by parsing should throw an error if the file is corrupted", "[Trailer]") {

    REQUIRE_THROWS_AS(oselin::Trailer("bla bla bla"), logic_error);
}

TEST_CASE("Constructor by parsing should throw an error if the file is empty", "[Trailer]") {

    REQUIRE_THROWS_AS(oselin::Trailer("<!--ch0--><!--cl0--><!--of0-->"), logic_error);
}

//
//
//TEST_CASE("tosvg should return 1 if some errors occur", "[oselin_to_svg]") {
//    
//    REQUIRE(oselin_to_svg(NULL)==1);
//
//    Parameters p;
//    p.svgwidth  = 800;
//    p.svgheight = 600;
//    p.length    = 100;
//    p.height    = 50;
//    p.radius    = 16;
//    p.ncars     = 2;
//    p.nfloors   = 2;
//
//    OselinDevice *dev = oselin_init(p);
//
//    REQUIRE(oselin_to_svg(dev) == 0);
//
//}
//
//TEST_CASE("trigonometry should return 1 if something bad happens", "[oselin_trigonometry]") {
//    
//    Parameters p;
//    p.svgwidth  = 800;
//    p.svgheight = 600;
//    p.length    = 100;
//    p.height    = 50;
//    p.radius    = 16;
//    p.ncars     = 2;
//    p.nfloors   = 2;
//
//    OselinDevice *dev = oselin_init(p);
//
//    REQUIRE(oselin_trigonometry(NULL)==1);
//    REQUIRE(oselin_trigonometry(dev)==0);
//
//    delete dev;
//}
//
//TEST_CASE("parsing should return empty string if nothing is fed into it", "[oselin_parsing]") {
//    
//    Parameters p;
//    p.svgwidth  = 800;
//    p.svgheight = 600;
//    p.length    = 100;
//    p.height    = 50;
//    p.radius    = 16;
//    p.ncars     = 2;
//    p.nfloors   = 2;
//
//    //OselinDevice *dev = oselin_init(p);
//    OselinDevice * dev;
//    dev = oselin_parsing("");
//    REQUIRE(dev->svg == "");
//
//    delete dev;
//
//}
//
//
//TEST_CASE("", "[oselin_set]") {
//    
//    //OselinDevice *oselin_set(OselinDevice *, int, float);
//}
//
//
//TEST_CASE("The function should return NULL fi something bad happens", "[oselin_init_acopyof]") {
//    
//    REQUIRE(oselin_init_acopyof(NULL)==NULL);
//}
//
//
//TEST_CASE("Creating and saving a brand new device. Checking if parsing works." "[oselin_parsing]"){
//
//    Parameters p;
//    p.svgwidth  = 800;
//    p.svgheight = 600;
//    p.length    = 100;
//    p.height    = 50;
//    p.radius    = 16;
//    p.ncars     = 2;
//    p.nfloors   = 2;
//
//    OselinDevice *dev = oselin_init(p);
//
//    oselin_trigonometry(dev);
//    oselin_to_svg(dev, true, true);
//    std::string filename = "testparsing.svg";
//    std::ofstream MyFile(filename);
//    MyFile << (dev->svg + "\n</svg>");
//    MyFile.close();
//    //---------------------------------------------    
//    std::ifstream file(filename);
//    std::stringstream buffer;
//    buffer << file.rdbuf();
//    std::string s = buffer.str();
//    OselinDevice *dev2 = oselin_parsing(s);
//    REQUIRE(dev->param.svgwidth     == dev2->param.svgwidth );
//    REQUIRE(dev->param.svgheight    == dev2->param.svgheight);
//    REQUIRE(dev->param.radius       == dev2->param.radius   );
//    REQUIRE(dev->param.length       == dev2->param.length   );
//    REQUIRE(dev->param.height       == dev2->param.height   );
//    REQUIRE(dev->param.ncars        == dev2->param.ncars    );
//    REQUIRE(dev->param.nfloors      == dev2->param.nfloors  );
//    REQUIRE(dev->param.margin       == dev2->param.margin   );
//
//
//
//    delete dev; delete dev2;
//}