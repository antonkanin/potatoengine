#pragma once
#include <vector>
#include "point_array.hpp"

struct point;

std::vector<point> make_line_float(point p1, point p2);

std::vector<point> make_line_int(point p1, point p2);

std::vector<point> make_triangle(point p1, point p2, point p3);

std::vector<point> make_triangle(const point_array& points);
