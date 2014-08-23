#pragma once

#include <ostream>


template<typename T>
struct Vector
{
    Vector() {}
    Vector(T x, T y, T z) :
	x(x), y(y), z(z) {}
    T x, y, z;    
    bool operator <(const Vector<T> &other) const
	{
	    if (this->x < other.x)
		return true;
	    if (this->x == other.x && this->y < other.y)
		return true;
	    if (this->x == other.x && this->y == other.y && this->z < other.z)
		return true;
	    return false;
	}
    
    virtual void print(std::ostream &out) { out << x << " " << y << " " << z << std::endl; }

    T distance_to(const Vector<T> &v) const;
};

#include "Vector-inl.hpp"
