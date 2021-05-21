#include "car_trailer.h"
#include "catch2/catch2.hpp"
#include <fstream>
#include <streambuf>
#include <sstream>
#include <string>
#include <iostream>

TEST_CASE("init should succeed with non zero value", "[oselin_init]") {

    Parameters p;
    p.svgwidth = 0;
    p.svgheight = 0;

    REQUIRE(oselin_init(p) == NULL);
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
    REQUIRE(oselin_trigonometry(dev)==0);

    delete dev;
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

    //OselinDevice *dev = oselin_init(p);
    OselinDevice * dev;
    dev = oselin_parsing("");
    REQUIRE(dev->svg == "");

    delete dev;

}


TEST_CASE("", "[oselin_set]") {
    
    //OselinDevice *oselin_set(OselinDevice *, int, float);
}


TEST_CASE("The function should return NULL fi something bad happens", "[oselin_init_acopyof]") {
    
    REQUIRE(oselin_init_acopyof(NULL)==NULL);
}


TEST_CASE("Creating and saving a brand new device. Checking if parsing works." "[oselin_parsing]"){

    Parameters p;
    p.svgwidth  = 800;
    p.svgheight = 600;
    p.length    = 100;
    p.height    = 50;
    p.radius    = 16;
    p.ncars     = 2;
    p.nfloors   = 2;

    OselinDevice *dev = oselin_init(p);

    oselin_trigonometry(dev);
    oselin_to_svg(dev, true, true);
    std::string filename = "testparsing.svg";
    std::ofstream MyFile(filename);
    MyFile << (dev->svg + "\n</svg>");
    MyFile.close();
    //---------------------------------------------    
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string s = buffer.str();
    OselinDevice *dev2 = oselin_parsing(s);
    REQUIRE(dev->param.svgwidth     == dev2->param.svgwidth );
    REQUIRE(dev->param.svgheight    == dev2->param.svgheight);
    REQUIRE(dev->param.radius       == dev2->param.radius   );
    REQUIRE(dev->param.length       == dev2->param.length   );
    REQUIRE(dev->param.height       == dev2->param.height   );
    REQUIRE(dev->param.ncars        == dev2->param.ncars    );
    REQUIRE(dev->param.nfloors      == dev2->param.nfloors  );
    REQUIRE(dev->param.margin       == dev2->param.margin   );



    delete dev; delete dev2;
}