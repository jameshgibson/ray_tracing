#pragma once

#include <map>
#include <set>
#include <vector>

#include "TestArea.hpp"
#include "Line.hpp"
#include "Vector.hpp"

typedef Vector<double> pointf_t;
typedef Vector<int> pointi_t;
typedef std::map<pointi_t, std::set<pointf_t > > point_map_t;
typedef std::map<pointi_t, std::vector<double> > length_map_t;
typedef std::map<pointi_t, std::set<int> > id_map_t;

class RayTracer
{
public:

    RayTracer(TestArea test_area);
    void process_line(int id, Line &line, double scaler);

    inline length_map_t get_lengths() { return length_map; }
    inline id_map_t get_ids() { return id_map; }

private:

    
    TestArea test_area;
    point_map_t point_map;
    length_map_t length_map;
    id_map_t id_map;

void process_intersections(int min, int max, Line &line, pointf_t (Line::*get_intersection)(double));
    void add_intersection_to_point_map(pointf_t &intersection);
    void add_lengths();
    void add_ids(int line_id);
    void add_adjacent_lengths(double scaler);
};
