
#include "../include/catch2/catch2.hpp"
#include "../include/car_trailer.h"


TEST_CASE("init should succeed with non zero value", "[oselin_init]") {

    float c[5], d[4];
    REQUIRE(oselin_init(NULL, c) == 1);

    OselinDevice *dev;

    REQUIRE(oselin_init(dev, d) == 1);
 
}


TEST_CASE("oselin init copy should not return null value", "[oselin_init_acopyof]") {
    REQUIRE(oselin_init_acopyof(NULL) != NULL);
}


TEST_CASE("oselin_parsing should not add to dev->svg if svg is empty", "[oselin_parsing]") {
    OselinDevice *dev = new OselinDevice;
    oselin_parsing(dev, "") ;
    REQUIRE(dev->svg == "");
   
}

TEST_CASE("my_div should give fraction as double", "[fraction]") {
    
}
