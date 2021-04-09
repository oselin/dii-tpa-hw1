
#include "my_fraction.h"
#include "iostream"

using namespace std;/*
 *  Source for the not-part-of-a-library class Fraction
 *
 */

MyFraction* my_init(int a, int b){

    if (b == 0){
        return NULL;
    }
    MyFraction* ret = new MyFraction;
    ret->a = a;
    ret->b = b;
    return ret;    
}

MyFraction* my_square(MyFraction * fraction) {
    
    MyFraction* ret = new MyFraction;
    ret->a = fraction->a * fraction->a;
    ret->b = fraction->b * fraction->b;
    return ret;
}


/** Divides numerator by denominator and returns the result.
 */
double my_div(MyFraction * fraction){
    return fraction->a / fraction->b;
}

void my_destroy(MyFraction* fraction){    
    delete fraction;  // works also if fraction is NULL    
}
