#pragma once
#include "point_array.hpp"
#include "vertex.hpp"
#include <vector>

struct point;
struct vertex;
struct image;

point_array make_line_float(point p1, point p2);

point_array make_line_int(point p1, point p2);

point_array make_solid_triangle(point p1, point p2, point p3);

point_array make_solid_triangle(const point_array& points);

point_array make_empty_triangle(const point p1, const point p2, const point p3);

vertex_array draw_interpolated_triangle(const vertex& vertex1,
                                        const vertex& vertex2,
                                        const vertex& vertex3);

void render_vertex_array(const std::vector<vertex>& vertexes,
                         /*out*/ image&             img);