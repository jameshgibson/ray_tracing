#include <cmath>
#include "Math.hpp"

template<typename T>
bool Vector<T>::operator <(const Vector<T> &other) const
{
    if (epsilon_equals(this->x, other.x) && epsilon_equals(this->y, other.y) && epsilon_equals(this->z, other.z))
	return false;
    
    if (!epsilon_equals(this->x, other.x) && this->x < other.x)
	return true;
    if (epsilon_equals(this->x, other.x) && !epsilon_equals(this->y, other.y) && this->y < other.y)
	return true;
    if (epsilon_equals(this->x, other.x) && epsilon_equals(this->y, other.y) && !epsilon_equals(this->z, other.z) && this->z < other.z)
	return true;
    return false;
}


template<typename T>
T Vector<T>::distance_to(const Vector<T> &v) const
{
    T xd = this->x - v.x;
    T yd = this->y - v.y;
    T zd = this->z - v.z;

    return std::sqrt(xd*xd + yd*yd + zd*zd);
}
