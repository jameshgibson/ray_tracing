#include "TestArea.hpp"

#include <cmath>
#include <iostream>

TestArea::TestArea(int x_max, int x_min, 
		   int y_max, int y_min, 
		   int z_max, int z_min,
		   int voxel_size) : x_min(x_min), x_max(x_max), 
				     y_min(y_min), y_max(y_max),
				     z_min(z_min), z_max(z_max),
				     voxel_size(voxel_size)
{ }


int TestArea::get_voxel(double val, int min, int precision = 1000)
{
    int ival = std::round(val * precision);
    min = min * precision;
    int scaled_voxel_size = voxel_size * precision;

    return std::abs((ival - min) / scaled_voxel_size);
}

int TestArea::get_corner(int val, int min)
{
    return val * voxel_size + min;
}

bool TestArea::on_plane(double val, int min, int precision = 1000)
{
    int ival = std::round(val * precision);
    min = min * precision;
    int scaled_voxel_size = voxel_size * precision;
    
    return (ival - min) % scaled_voxel_size == 0;    
}

std::vector<Vector<int> > TestArea::get_voxels(Vector<double> &point)
{
    std::vector<Vector<int> > voxels;

    int x_comp = get_voxel(point.x, x_min);
    int y_comp = get_voxel(point.y, y_min);
    int z_comp = get_voxel(point.z, z_min);
    
    if (on_plane(point.x, x_min) 
	&& y_comp < y_voxel_limit() 
	&& z_comp < z_voxel_limit())
    {
	if (x_comp - 1 >= 0 && x_comp - 1 < x_voxel_limit())
	{
	    voxels.push_back(Vector<int>((x_comp - 1), y_comp, z_comp));
	}
    }

    if (on_plane(point.y, y_min)
	&& x_comp < x_voxel_limit() 
	&& z_comp < z_voxel_limit())
    {
	if (y_comp - 1 >= 0 && y_comp - 1 < y_voxel_limit())
	{
	    voxels.push_back(Vector<int>(x_comp, (y_comp - 1), z_comp));
	}
    }

    if (on_plane(point.z, z_min)
	&& x_comp < x_voxel_limit() 
	&& y_comp < y_voxel_limit())
    {
	if (z_comp - 1 >= 0 && z_comp - 1 < z_voxel_limit())
	{
	    voxels.push_back(Vector<int>(x_comp, y_comp, (z_comp - 1)));
	}
    }

    if (x_comp < x_voxel_limit() && y_comp < y_voxel_limit() && z_comp < z_voxel_limit())
    {
	voxels.push_back(Vector<int>(x_comp, y_comp, z_comp));
    }
    
    return voxels;   
}

bool TestArea::contains(Vector<double> &point)
{
    if (point.x <= x_max && point.x >= x_min &&
	point.y <= y_max && point.y >= y_min &&
	point.z <= z_max && point.z >= z_min)
    {
	return true;
    }
    return false;	
}
