
#include "cxx_examples.h"
#include <cmath>
#include "iostream"


double cxx_examples::square_root(double x){
    if (x < 0.0){
        throw std::invalid_argument("Negative number!"); // stops program here (if not catched)
    }
    return sqrt(x);
}
    
std::string cxx_examples::say_hello(const char* name){
    std::string ret = "hello ";
    ret += name;
    return ret;
}

