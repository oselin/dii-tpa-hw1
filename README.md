# DII - TPA: Homework 1

First homework of the Advanced Programming Techniques course. Dealine 2021-04-27

For usage, read below.
## Car Trailer

Create a car trailer basing on car's parameters you need to transport.

It's possible to export the generated drawing as .svg file.

With this tool you can obtain several devices, some of them in the following.

### Car trailer for 2 cars-per-floor. 2 floors
![](output/twofloorstwocars.svg)

### Car trailer for 2 cars-per-floor. 1 floor
![](output/onefloortwocars.svg)


### Car trailer for 1 cars-per-floor. 1 floor
![](output/oneflooronecar.svg)

### Car trailer for 1 cars-per-floor. 2 floors

This would be structurally unstable. By this, the configuration is not allowed.

### Measures aviable as well
![](output/twofloorstwocarsm.svg)

## Machines aviable as well
These are combination of multiple devices, with the implementation of a car's .svg file. A big thanks to **@GiacomoCorradini** and his awesome work.

![](output/machine.svg)

# USAGE
## Constrains
There are some constrains you need to deal with:
- Trailer's length must be smaller than canvas width
- Trailer's height must be smaller than 5/4 canvas height
- 2 floors one car configuration is not allowed to preserve structural stability
- Car's length can't be smaller than 4/5 car's height (van configuration)
- More than 2 cars per trailer are not allowed
- More than 2 floors are not allowed

## Commands

Initialization of a trailer
~~~C++
OselinDevice *trailer;
~~~

All the data referred to trailer's dimensions and parameters are stored in the **OselinDevice** struct. Probably not the most efficient way to manage memory, but it definitely does the job.

~~~C++
oselin_init(OselinDevice *trailer, float params[], bool avoidsvg = false);
~~~

This function returns 0 if every single parameter given by the user respects the constrains, 1 otherwise. The boolean avoidsvg, if set to true, allows to bypass the svg width/height constrain check. It can be used for machine manipulations. However by default is set to false.

~~~C++
oselin_trigonometry(OselinDevice *trailer, bool automaticoffset=true);
~~~

This void function does all the math that allows the creation of SVG figures.

~~~C++
oselin_to_svg(OselinDevice *trailer, bool with_header=true, bool with_measures=false);
~~~

This function fills the .svg attribute of the trailer with drawing infos, svg-coded.