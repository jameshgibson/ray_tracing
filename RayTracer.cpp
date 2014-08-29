#include "RayTracer.hpp"

RayTracer::RayTracer(TestArea test_area) : test_area(test_area) {}

void RayTracer::process_line(int id, Line &line, double scaler)
{
    process_intersections(test_area.get_x_min(), test_area.get_x_max(), line, &Line::x_intersection);
    process_intersections(test_area.get_y_min(), test_area.get_y_max(), line, &Line::y_intersection);
    process_intersections(test_area.get_z_min(), test_area.get_z_max(), line, &Line::z_intersection);

    add_lengths();
    add_ids(id);
    add_adjacent_lengths(scaler);
    point_map.clear();
}

void RayTracer::process_intersections(int min, int max, Line &line, pointf_t (Line::*get_intersection)(double))
{
    for (; min <= max; min += test_area.get_voxel_size())
    {
	pointf_t intersection = (line.*get_intersection)(min);
	add_intersection_to_point_map(intersection);
    }
}

void RayTracer::add_intersection_to_point_map(pointf_t &intersection)
{
    if (test_area.contains(intersection))
    {
	std::vector<pointi_t> voxels = test_area.get_voxels(intersection);
	std::vector<pointi_t>::iterator iter = voxels.begin();
	for (; iter != voxels.end(); ++iter)
	{
	    if (point_map.find(*iter) != point_map.end())
	    {
		point_map[*iter].insert(intersection);
	    }
	    else
	    {
		std::set<pointf_t> new_points;
		new_points.insert(intersection);
		point_map.insert(std::make_pair(*iter, new_points));
	    }
	}
    }
}

void RayTracer::add_lengths()
{
    point_map_t::iterator iter = point_map.begin();
    for (; iter != point_map.end(); ++iter)
    {
	if (iter->second.size() == 2)
	{
	    pointi_t pos = iter->first;
	    std::set<pointf_t>::iterator sps = iter->second.begin();
	    pointf_t one = *sps;
	    pointf_t two = *(++sps);
	    
	    double dist = one.distance_to(two);

	    if (length_map.find(pos) == length_map.end())
	    {
		std::vector<double> dists;
		dists.push_back(dist);
		length_map.insert(std::make_pair(pos, dists));
	    }
	    else
	    {
		length_map[pos].push_back(dist);
	    }
	}
    }

}

void RayTracer::add_adjacent_lengths(double scaler)
{
    point_map_t::iterator iter = point_map.begin();
    for(; iter != point_map.end(); ++iter)
    {
	if (iter->second.size() == 2)
	{

	    pointi_t position = iter->first;

	    std::set<pointf_t>::iterator sps = iter->second.begin();
	    pointf_t one = *sps;
	    pointf_t two = *(++sps);
	    double len = one.distance_to(two);
	    len *= scaler;

	    std::map<pointi_t, double> adjs;

	    for (int x = position.x - 1; x <= position.x + 1; ++x)
	    {
		for (int y = position.y - 1; y <= position.y + 1; ++y)
		{
		    for (int z = position.z - 1; z <= position.z + 1; ++z)
		    {
			pointi_t adj = pointi_t(x, y, z);

			if (point_map.find(adj) == point_map.end())
			{
			    if (adjs.find(adj) == adjs.end())
			    {
			        adjs.insert(std::make_pair(adj, len));
			    }
			}
		    }
		}
	    }

	    for (std::map<pointi_t, double>::iterator it = adjs.begin(); 
		 it != adjs.end(); ++it)
	    {
		if (length_map.find(it->first) == length_map.end())
		{
		    std::vector<double> lens;
		    lens.push_back(it->second);
		    length_map.insert(std::make_pair(it->first, lens));
		}
		else
		{
		    length_map[it->first].push_back(len);
		}
	    }

	}
    }
}

void RayTracer::add_ids(int line_id)
{
    point_map_t::iterator iter = point_map.begin();
    for (; iter != point_map.end(); ++iter)
    {
	pointi_t pos = iter->first;
	    
	if (id_map.find(pos) == id_map.end())
	{
	    std::set<int> ids;
	    ids.insert(line_id);
	    id_map.insert(std::make_pair(pos, ids));
	}
	else
	{
	    id_map[pos].insert(line_id);
	}
    }
}





