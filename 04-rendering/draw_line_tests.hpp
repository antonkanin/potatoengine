#pragma once

#include <string>

#include "draw_utils.hpp"

void render_lines_list_test(std::vector<std::pair<point, point>> lines,
                            const std::string&                   image_name,
                            std::vector<point> (*make_line_func)(point, point));

void draw_line_tests(std::vector<point> (*make_line_func)(point, point));

void render_test_triangle();

void render_line_test(const std::vector<point>& line,
                      const std::string&        image_name);
