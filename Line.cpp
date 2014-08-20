#include "Line.hpp"

#include <cmath>

Line::Line(Vector<double> position, Vector<double> direction_cosines) :
    position(position)
{
    m = Vector<double>(direction_cosines.x,
		       direction_cosines.y,
		       direction_cosines.z);
}

bool Line::intersects_with(Vector<double> plane)
{
    if (plane.x != 0)  return m.x != 0;
    if (plane.y != 0)  return m.y != 0;
    if (plane.z != 0)  return m.z != 0;
    return false;
}

Vector<double> Line::x_intersection(double x)
{
    Vector<double> intersection;
    double t = (x - position.x) / m.x;
    intersection.x = x;
    intersection.y = position.y + t * m.y;
    intersection.z = position.z + t * m.z;
    return intersection;
}

Vector<double> Line::y_intersection(double y)
{
    Vector<double> intersection;
    double t = (y - position.y) / m.y;
    intersection.y = y;
    intersection.x = position.x + t * m.x;
    intersection.z = position.z + t * m.z;
    return intersection;	
}

Vector<double> Line::z_intersection(double z)
{
    Vector<double> intersection;
    double t = (z - position.z) / m.z;
    intersection.z = z;
    intersection.y = position.y + t * m.y;
    intersection.x = position.x + t * m.x;
    return intersection;	
}





