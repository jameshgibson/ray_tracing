#pragma once

#include <vector>
#include <map>

#include "Vector.hpp"

class TestArea
{
public:

    TestArea(int x_max, int x_min, 
	     int y_max, int y_min, 
	     int z_max, int z_min,
	     int voxel_size);

    std::vector<Vector<int> > get_voxels(Vector<double> &point);    
    bool contains(Vector<double> &point);
    int get_corner(int, int);

    inline int get_x_min() { return x_min; }
    inline int get_y_min() { return y_min; }
    inline int get_z_min() { return z_min; }

    inline int get_x_max() { return x_max; }
    inline int get_y_max() { return y_max; }
    inline int get_z_max() { return z_max; }

    inline int get_voxel_size() { return voxel_size; }
private:

    inline int x_voxel_limit() { return (x_max - x_min) / voxel_size; }
    inline int y_voxel_limit() { return (y_max - y_min) / voxel_size; }
    inline int z_voxel_limit() { return (z_max - z_min) / voxel_size; }
    
    int get_voxel(double, int, int);
    bool on_plane(double, int, int);

    int x_min, x_max,
	y_min, y_max,
	z_min, z_max,
	voxel_size;
};
