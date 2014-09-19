#include <iostream>
#include <fstream>
#include <map>
#include <cstring>
#include <cstdlib>

#include "TestArea.hpp"
#include "Line.hpp"
#include "Vector.hpp"
#include "Math.hpp"
#include "RayTracer.hpp" 

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


int main(int argc, char *argv[])
{
    int x_max = 2500, x_min = -x_max;
    int y_max = 2500, y_min = -y_max;
    int z_max = 2500, z_min = -2500;
 
    int voxel_size = 50;
    double length_scaler = 0.5;
    unsigned int min_intersections = 2;
    if (argc > 3)
    {
	min_intersections = std::atoi(argv[3]);
    }

    TestArea test_area(x_max, x_min, y_max, y_min, z_max, z_min, voxel_size);

    RayTracer ray_tracer(test_area);

    std::ifstream muons(argv[1]);
    std::map<int, Line> lines = read_lines(muons);

    if (argc > 2) 
    {
	if (std::strcmp(argv[2], "false") == 0) ray_tracer.should_add_adjacents(false);
	if (std::strcmp(argv[2], "true") != 0 && std::strcmp(argv[2], "false") != 0) 
	{
	    std::cout << "arguments wrong:\n\n\t usage: ./ra muon_file [true|false] [min_intersections]" << std::endl;
	    return 1;
	}
    }
      
    for (std::map<int, Line>::iterator it = lines.begin(); 
	 it != lines.end(); ++it)
    {
	ray_tracer.process_line(it->first, it->second, length_scaler);	
    }

    length_map_t length_map = ray_tracer.get_lengths();
    id_map_t id_map = ray_tracer.get_ids();

    length_map_t::iterator iter = length_map.begin();
    for (; iter != length_map.end(); ++iter)
    {
	if (iter->second.size() < min_intersections) continue;

	pointi_t pos = iter->first;
	double dist = sum(iter->second);
	
	//std::cout << pos.x << " " << pos.y << " " << pos.z << " " << dist << std::endl;
	std::cout << test_area.get_corner(pos.x, x_min) << " " 
		  << test_area.get_corner(pos.y, y_min) << " " 
		  << test_area.get_corner(pos.z, z_min) << " " 
		  << dist << " ";

	std::set<int> ids = id_map[pos];
	for (std::set<int>::iterator it = ids.begin(); it != ids.end(); ++it)
	{
	    std::cout << *it << ",";
	}
	std::cout << std::endl;
    }

    return 0;
}
