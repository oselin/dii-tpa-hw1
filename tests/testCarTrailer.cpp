
#include "catch2/catch2.hpp"
#include "car_trailer.h"


TEST_CASE("Init should return 1 if any error occurs", "[oselin_init]") {
    
    float c[5], d[4];
    REQUIRE(oselin_init(NULL, c) == 1);
    OselinDevice *dev;
    REQUIRE(oselin_init(dev, d) == 1);
}


TEST_CASE("trigonometry should call error function", "[oselin_trigonometry]") {
       
       OselinDevice *dev = NULL;

       oselin_trigonometry(dev);
       REQUIRE(dev == NULL);
}


TEST_CASE("my_square should return a new squared fraction", "[fraction]") {

   
}

TEST_CASE("my_div should give fraction as double", "[fraction]") {
    
}



