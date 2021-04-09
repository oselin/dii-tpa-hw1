#include <iostream>

#include "my_fraction.h"
#include "cxx_examples.h"

using namespace std;

int main() {


    MyFraction * frac = my_init(3,5);

    cout << "MyFraction: " << frac->a << " / " << frac->b << endl;

    cout << "say_hello: " << cxx_examples::say_hello("Peppo") << endl;

    try {
        cout << "negative square_root: " << cxx_examples::square_root(-1.0) << endl;
    } catch (exception& ex) {
        cout << "something bad happened!" << ex.what() << endl;
        cout << "I caught the exception, will continue" << endl;
    };

    cout << "end of the program!" << endl;

    return 0;
}
