#include "machine_car_trailer.h"
#include "catch2/catch2.hpp"
#include <fstream>
#include <streambuf>
#include <sstream>
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;


TEST_CASE("Machine: Constructor should throw as car_length is too much", "[Machine]") {

    oselin::Parameters p;
    p.car_radius(17);
    p.car_length(2000);
    p.car_height(50);
    p.n_cars(2);
    p.n_floors(2);
    
    REQUIRE_THROWS_AS(oselin::Machine(p,1), invalid_argument);
}


TEST_CASE("Machine: Constructor should throw as cars are too many", "[Machine]") {

    oselin::Parameters p;

    p.car_radius(17);
    p.car_length(150);
    p.car_height(50);
    p.n_cars(4);
    p.n_floors(2);
    
    REQUIRE_THROWS_AS(oselin::Machine(p,1), out_of_range);
}


TEST_CASE("Machine: Constructor should throw as floors are too many", "[Machine]") {

    oselin::Parameters p;

    p.car_radius(17);
    p.car_length(150);
    p.car_height(50);
    p.n_cars(2);
    p.n_floors(6);
    
    REQUIRE_THROWS_AS(oselin::Machine(p,1), out_of_range);
}

TEST_CASE("Machine: Constructor should throw as cars are too short", "[Machine]") {

    oselin::Parameters p;

    p.car_radius(17);
    p.car_length(20);
    p.car_height(50);
    p.n_cars(2);
    p.n_floors(2);
    
    REQUIRE_THROWS_AS(oselin::Machine(p,1), invalid_argument);
}


TEST_CASE("Machine: Constructor should throw as structural error", "[Machine]") {

    oselin::Parameters p;

    p.car_radius(17);
    p.car_length(150);
    p.car_height(50);
    p.n_cars(1);
    p.n_floors(2);
    REQUIRE_THROWS_AS(oselin::Machine(p,1), invalid_argument);
}
TEST_CASE("Machine: Constructor should throw as radius error", "[Machine]") {

    oselin::Parameters p;

    p.car_radius(2);
    p.car_length(150);
    p.car_height(50);
    p.n_cars(1);
    p.n_floors(2);
    REQUIRE_THROWS_AS(oselin::Machine(p,1), out_of_range);
}


TEST_CASE("Machine: Constructor by parsing should throw an error if the file is corrupted", "[Machine]") {

    REQUIRE_THROWS_AS(oselin::Machine("bla bla bla"), logic_error);
}

TEST_CASE("Machine: Constructor by parsing should throw an error if the file is empty", "[Machine]") {

    REQUIRE_THROWS_AS(oselin::Machine("<!--ch0--><!--cl0--><!--of0-->"), logic_error);
}

TEST_CASE("Machine: Constructor by parameters should throw as the lenth is <= 0", "[Machine]") {

    oselin::Parameters p;

    p.car_radius(17);
    p.car_length(150);
    p.car_height(50);
    p.n_cars(1);
    p.n_floors(2);

    REQUIRE_THROWS_AS(oselin::Machine(p,0), out_of_range);
    REQUIRE_THROWS_AS(oselin::Machine(p,-12), out_of_range);
}


//TEST_CASE("init should return NULL value if parameters are  wrong ", "[oselin_machine_init]"){
//
//    OselinDevice dev;
//    int ntrailers = -2;
//    Parameters p;
//    p.svgwidth  = 0;
//    p.svgheight = 0;
//
//    REQUIRE(oselin_machine_init(p, ntrailers)==NULL);
//
//    REQUIRE(oselin_machine_init(p, 0)==NULL);
//}
//
//TEST_CASE("tostring function should return empty string if parameters are wrong","oselin_machine_to_string"){
//    OselinMachine *mach = NULL;
//    REQUIRE(oselin_machine_to_string(mach)=="");
//
//    //REQUIRE(oselin_machine_to_string(&mach)=="");
//}
//
//TEST_CASE("tosave should not save if parameters are wrong","oselin_machine_save"){
//    OselinMachine *mach = new OselinMachine;
//    
//    
//    mach->parameters.length = 0;
//    oselin_machine_save(mach);
//
//    oselin_machine_save(NULL);
//
//}
//
//TEST_CASE("parsing should ...","oselin_machine_parsing"){
//
//}
//