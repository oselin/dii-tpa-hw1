#ifndef MY_CXX_EXAMPLES_H
#define MY_CXX_EXAMPLES_H


/*
 * C++-style examples
 * 
 */

#include <stdexcept>
#include <string>


namespace cxx_examples {
    

    /**
     * Return the square root of x
     * 
     * - if x is negative, throws std::invalid_argument
    */
    double square_root(double x);

    /**
     * Returns a new string saying hello to name
     *      
    */
    std::string say_hello(const char* name);

}


#endif // MY_CXX_EXAMPLES
