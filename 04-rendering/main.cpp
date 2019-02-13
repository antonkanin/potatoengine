#include "draw_line_tests.hpp"

#include "image.hpp"
#include "mesh.hpp"
#include "point.hpp"
#include "point_array.hpp"
#include <cstdlib>

int main(int argc, char* argv[])
{
    image img(800, 600);

    //
    ///////////////////////////////////////////////////////////////////////////
    // 01 draw a single line

    img.fill(white)
        .draw(make_line_int({ 100, 100 }, { 700, 500 }), black)
        .save("01_line.ppm");

    //
    ///////////////////////////////////////////////////////////////////////////
    // 02 draw a triangle with lines

    img.fill(white)
        .draw(make_solid_triangle({10, 10}, {90, 90}, {30, 60}), black)
        .save("02_triangle.ppm");

    //
    ///////////////////////////////////////////////////////////////////////////
    // 03 draw multiple random triangles

    img.set_size(800, 600).fill(white);

    for (uint8_t counter = 0; counter < 10; ++counter)
    {
        point_array points;

        for (uint8_t v_index = 0; v_index < 3; ++v_index)
        {
            auto x = static_cast<uint16_t>(random() % img.width());
            auto y = static_cast<uint16_t>(random() % img.height());

            points.push_back({ x, y });
        }

        color clr = { static_cast<uint8_t>(random() % 255),
                      static_cast<uint8_t>(random() % 255),
                      static_cast<uint8_t>(random() % 255) };

        img.draw(make_line_int(points[0], points[1]), clr)
            .draw(make_line_int(points[1], points[2]), clr)
            .draw(make_line_int(points[2], points[0]), clr);
    }

    img.save("03_random_triangles.ppm");

    //
    ///////////////////////////////////////////////////////////////////////////
    // 04 draw multiple triangle using vertex buffer (VB) and index buffer (IB)

    img.fill(white);

    mesh mesh_obj;
    mesh_obj.points  = { { 10, 10 }, { 10, 20 }, { 20, 10 }, { 20, 20 } };
    mesh_obj.indexes = { 1, 2, 3, 2, 3, 4 };

    for (uint16_t index = 0; index < mesh_obj.indexes.size() - 3; index += 3)
    {
        auto p1 = mesh_obj.points[mesh_obj.indexes[index]];
        auto p2 = mesh_obj.points[mesh_obj.indexes[index + 1]];
        auto p3 = mesh_obj.points[mesh_obj.indexes[index + 2]];

        auto tri = make_empty_triangle(p1, p2, p3);

        img.draw(tri, black);
    }

    img.save("04_VB_IB_triangles.ppm");

    //
    ///////////////////////////////////////////////////////////////////////////
    // 05 draw interpolated triangle with filling

    // TODO ...

    //
    ///////////////////////////////////////////////////////////////////////////
    // 06 draw textured triangle

    // TODO ...

    return EXIT_SUCCESS;
}