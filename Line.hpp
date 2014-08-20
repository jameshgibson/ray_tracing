#pragma once

#include "Vector.hpp"

class Line
{
public:

    Line() {}
    Line(Vector<double> position, Vector<double> direction_cosines);
    bool intersects_with(Vector<double> plane);
    Vector<double> x_intersection(double x);
    Vector<double> y_intersection(double y);
    Vector<double> z_intersection(double z);


private:

    Vector<double> position;
    Vector<double> m;
};
