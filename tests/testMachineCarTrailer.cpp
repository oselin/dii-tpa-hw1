#include "machine_car_trailer.h"
#include "catch2/catch2.hpp"


TEST_CASE("init should return NULL value if parameters are  wrong ", "[oselin_machine_init]"){

    OselinDevice dev;
    int ntrailers = -2;
    Parameters p;
    p.svgwidth  = 0;
    p.svgheight = 0;

    REQUIRE(oselin_machine_init(p, ntrailers)==NULL);

    REQUIRE(oselin_machine_init(p, 0)==NULL);
}

TEST_CASE("tostring function should return empty string if parameters are wrong","oselin_machine_to_string"){
    OselinMachine *mach = NULL;
    REQUIRE(oselin_machine_to_string(mach)=="");

    //REQUIRE(oselin_machine_to_string(&mach)=="");
}

TEST_CASE("tosave should not save if parameters are wrong","oselin_machine_save"){
    OselinMachine *mach = new OselinMachine;
    
    
    mach->parameters.length = 0;
    oselin_machine_save(mach);

    oselin_machine_save(NULL);

}

TEST_CASE("parsing should ...","oselin_machine_parsing"){

}
