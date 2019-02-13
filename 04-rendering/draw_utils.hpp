#pragma once
#include <vector>
#include "point_array.hpp"

struct point;

point_array make_line_float(point p1, point p2);

point_array make_line_int(point p1, point p2);

point_array make_solid_triangle(point p1, point p2, point p3);

point_array make_solid_triangle(const point_array &points);

point_array make_empty_triangle(const point p1, const point p2, const point p3);


