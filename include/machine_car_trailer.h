
#ifndef MACHINE_CAR_TRAILER_H
#define MACHINE_CAR_TRAILER_H

#include <string>
#include <unordered_map>
#include <iostream>
#include <ostream>
#include <vector>

#include "car_trailer.h"
#include "Car.h"


using std::string;
using std::ostream;
using std::vector;

namespace oselin{
    class Machine: public oselin::Parameters{
        private:
            vector<oselin::Trailer *> trailer_array_;
            vector<coca_device*>    car_array_;
            float                   n_trailers_;

            void print(ostream&) const;

        public:
            Machine();

            Machine(const Machine &);
            Machine(oselin::Parameters, float);

            Machine(string);

            string svg() const;

            void  n_trailers(float);
            float n_trailers() const;

            void copyParam(oselin::Parameters, float);
    };

    //coca_device * oselin_coca_init(oselin::Parameters *, float, float);
};

#endif //MACHINE_CAR_TRAILER_H   