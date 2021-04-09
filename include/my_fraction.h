#ifndef MY_FRACTION_H
#define MY_FRACTION_H

/*
 * A C-style library for fractions
 */

/**
 * 
 * A struct representing a fraction  
**/
struct MyFraction {
    double a;
    double b;
};


/** Creates a NEW Fraction with provided numerator and denominator
 * 
 *  - if b is zero, returns NULL  (C-style error signalling)
 */
MyFraction* my_init(int a, int b);

 
/** Creates a NEW Fraction which is the square of the provided one
 */
MyFraction* my_square(MyFraction * fraction);


/** Divides numerator by denominator and returns the result.
 */
double my_div(MyFraction * fraction);


/**
 *  Deletes fraction
 */
void my_destroy(MyFraction* fraction);


#endif //MY_FRACTION_H
