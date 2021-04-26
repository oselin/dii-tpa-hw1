# Sources that contain the tests
add_executable(catch2Test catch2Main.cpp) # Just this one contains BOOST_TEST_MAIN
target_sources(catch2Test PRIVATE testCarTrailer.cpp)


# Libraries used in the tests
target_link_libraries(catch2Test)

# Including headers
target_include_directories(catch2Test PRIVATE
        ../include) # Including this allows to simply write #include "funcs.h"
target_include_directories(catch2Test PRIVATE
        ../TpaHomework1/include)

# Including sources
target_sources(catch2Test PRIVATE
        ../src/CarTrailer.cpp)
target_sources(catch2Test PRIVATE
        ../src/MachineCarTrailer.cpp)
target_sources(catch2Test PRIVATE
        ../TpaHomework1/src/Car.cpp)

#target_compile_options(catch2Test PRIVATE -Wa,-mbig-obj) # Solves assembler error of file too big