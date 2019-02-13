#pragma once

#include <ostream>
#include <vector>

struct point;

typedef std::vector<point> point_array;

point_array operator+(const point_array& lhs, const point& rhs);

std::ostream& operator<<(std::ostream& out, const point_array& points);

point_array operator+(const point_array& lhs, const point_array& rhs);

// flips points array around the max Y value
point_array flip_y(const point_array& points);
