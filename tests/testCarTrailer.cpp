
#include "../include/catch2/catch2.hpp"
#include "../include/car_trailer.h"
#include <iostream>
using namespace std;
TEST_CASE("init should succeed with non zero value", "[oselin_init]") {

    Parameters p;
    p.svgwidth =0;
    p.svgheight = 0;

    REQUIRE(oselin_init(p) == NULL);
    cout << "aa" << endl;
    p.svgwidth = 800;
    p.svgheight = 600;
    p.ncars = 1;
    p.nfloors = 2;
    REQUIRE(oselin_init(p) == NULL);


}


TEST_CASE("oselin init copy should not return null value", "[oselin_init_acopyof]") {
    REQUIRE(oselin_init_acopyof(NULL) == NULL);

    Parameters p;
    p.svgwidth  = 800;
    p.svgheight = 600;
    p.length    = 100;
    p.height    = 50;
    p.radius    = 16;
    p.ncars     = 2;
    p.nfloors   = 2;

    REQUIRE(oselin_init_acopyof(oselin_init(p)) != NULL);

}


TEST_CASE("tosvg should return 1 if some errors occur", "[oselin_to_svg]") {
    
    REQUIRE(oselin_to_svg(NULL)==1);

    Parameters p;
    p.svgwidth  = 800;
    p.svgheight = 600;
    p.length    = 100;
    p.height    = 50;
    p.radius    = 16;
    p.ncars     = 2;
    p.nfloors   = 2;

    OselinDevice *dev = oselin_init(p);

    REQUIRE(oselin_to_svg(dev) == 0);

}

TEST_CASE("trigonometry should return 1 if something bad happens", "[oselin_trigonometry]") {
    
    Parameters p;
    p.svgwidth  = 800;
    p.svgheight = 600;
    p.length    = 100;
    p.height    = 50;
    p.radius    = 16;
    p.ncars     = 2;
    p.nfloors   = 2;

    OselinDevice *dev = oselin_init(p);

    REQUIRE(oselin_trigonometry(NULL)==1);
}



TEST_CASE("parsing should return empty string if nothing is fed into it", "[oselin_parsing]") {
    
    Parameters p;
    p.svgwidth  = 800;
    p.svgheight = 600;
    p.length    = 100;
    p.height    = 50;
    p.radius    = 16;
    p.ncars     = 2;
    p.nfloors   = 2;

    OselinDevice *dev = oselin_init(p);
    oselin_parsing(dev,"");
    REQUIRE(dev->svg =="");

}


TEST_CASE("", "[oselin_set]") {
    
    //OselinDevice *oselin_set(OselinDevice *, int, float);
}

TEST_CASE("The function should return NULL fi something bad happens", "[oselin_init_acopyof]") {
    
    REQUIRE(oselin_init_acopyof(NULL)==NULL);
}



