#include <cmath>

template<typename T>
T Vector<T>::distance_to(const Vector<T> &v) const
{
    T xd = this->x - v.x;
    T yd = this->y - v.y;
    T zd = this->z - v.z;
    
    return std::sqrt(xd*xd + yd*yd + zd*zd);
}
