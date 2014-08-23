#include <iostream>
#include <fstream>
#include <map>
#include <set>

#include "TestArea.hpp"
#include "Line.hpp"
#include "Vector.hpp"

std::map<int, Line> read_lines(std::ifstream &is)
{
    std::map<int, Line> lines;
    int id;
    double x, y, z, mx, my, mz;
    while (is >> id >> x >> y >> z >> mx >> my >> mz)
    {
	Line line = Line(Vector<double>(x, y, z), Vector<double>(mx, my, mz));
	lines.insert(std::make_pair(id, line));
    }
    return lines;
}

double average(std::vector<double> &nums)
{
    double avg = 0;
    for (std::vector<double>::iterator it = nums.begin();
	 it != nums.end(); ++it)
    {
	avg += *it;
    }
    return avg / (double)nums.size();
}

void process_line(Line &line, Vector<double> &intersection, TestArea &test_area, std::map<Vector<int>, std::set<Vector<double> > > &points)
{
    if (test_area.contains(intersection))
    {
	std::vector<Vector<int> > vox = test_area.get_voxels(intersection);

	for (std::vector<Vector<int> >::iterator it = vox.begin(); 
	     it != vox.end(); ++it)
	{   
	    if (points.find(*it) != points.end()) 
	    {	
	    	points[*it].insert(intersection);
	    }
	    else
	    {
	    	std::set<Vector<double> > np;
	    	np.insert(intersection);
	    	points.insert(std::make_pair(*it, np));
	    }
	}
    }
}

int main(int argc, char *argv[])
{
    int x_max = 2500, x_min = -x_max;
    int y_max = 2500, y_min = -y_max;
    int z_max = 2500, z_min = -2500;
 
    int voxel_size = 50;
    double length_scaler = 1;


    TestArea test_area(x_max, x_min, y_max, y_min, z_max, z_min, voxel_size);

    std::ifstream muons(argv[1]);
    std::map<int, Line> lines = read_lines(muons);

    std::map<int, std::set<Vector<double> > > voxel_points;
    std::map<Vector<int>, std::vector<double> > lengths;

    for (std::map<int, Line>::iterator it = lines.begin(); 
	 it != lines.end(); ++it)
    {
	Line line = it->second;
	std::map<Vector<int>, std::set<Vector<double> > > points;

	for (int x = x_min; x <= x_max; x += voxel_size)
	{
	   
	    Vector<double> intersection = line.x_intersection(x);   
	    process_line(line, intersection, test_area, points);
	}

	for (int y = y_min; y <= y_max; y += voxel_size)
	{
	    Vector<double> intersection = line.y_intersection(y);
	    process_line(line, intersection, test_area, points);
	}
	
	for (int z = z_min; z <= z_max; z += voxel_size)
	{
	    Vector<double> intersection = line.z_intersection(z);
	    process_line(line, intersection, test_area, points);
	}

	for (std::map<Vector<int>, std::set<Vector<double> > >::iterator it = points.begin();
	     it != points.end(); ++it)
	{
	    Vector<int> pos = it->first;
	    if (it->second.size() == 2)
	    {
		std::set<Vector<double> >::iterator sps = it->second.begin();
		Vector<double> one = *sps;
		Vector<double> two = *(++sps);
		double dist = one.distance_to(two);

		dist *= length_scaler;

		if (lengths.find(pos) == lengths.end())
		{
		    std::vector<double> dists;
		    dists.push_back(dist);
		    lengths.insert(std::make_pair(pos, dists));
		}
		else
		{
		    lengths[pos].push_back(dist);
		}
	    }
	}
    }

    for (std::map<Vector<int>, std::vector<double> >::iterator it = lengths.begin();
    	 it != lengths.end(); ++it)
    {
    	std::cout << test_area.get_corner(it->first.x, x_min) << " " 
    		  << test_area.get_corner(it->first.y, y_min) << " " 
    		  << test_area.get_corner(it->first.z, z_min) << " " 
    		  << average(it->second) << std::endl;
    }

    

    return 0;
}
