#include "read_obj.hpp"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>

namespace pt
{

unsigned short get_vertex_id(const std::string& string_id)
{
    using namespace std;
    auto pos = string_id.find('/');
    if (pos == string::npos)
    {
        return static_cast<uint16_t>(stoi(string_id));
    }
    else
    {
        string result = string_id.substr(0, pos);
        return static_cast<uint16_t>(stoi(result));
    }
}

model read_obj(const std::string& file_name)
{
    std::ifstream file(file_name);

    if (!file.is_open())
    {
        throw std::runtime_error("Error: failed to open file " + file_name);
    }

    model result{};

    std::string line;
    while (getline(file, line))
    {
        if (line.length() == 0)
        {
            continue;
        }

        // reading vertices
        if (line[0] == 'v' && line[1] == ' ')
        {
            std::stringstream ss(line);

            float x, y, z;
            char  garbage;

            ss >> garbage >> x >> y >> z;

            result.vertices.push_back({ x, y, z });
        }

        // reading faces (triangles or quads)
        if (line[0] == 'f')
        {
            // 4 spaces - it's a quad
            // 3 spaces - it's a triangle
            const auto space_count = std::count(begin(line), end(line), ' ');
            const bool is_quad     = (4 == space_count);

            std::stringstream ss(line);
            std::string       f1, f2, f3, f4;
            char              garbage;

            ss >> garbage >> f1 >> f2 >> f3;
            if (is_quad)
            {
                ss >> f4;
            }

            // for triangle we  simply load 1st, 2nd, 3rd vertexes
            result.indices.push_back(
                static_cast<unsigned int&&>(get_vertex_id(f1) - 1));

            result.indices.push_back(
                static_cast<unsigned int&&>(get_vertex_id(f2) - 1));

            result.indices.push_back(
                static_cast<unsigned int&&>(get_vertex_id(f3) - 1));

            // if it's a quad we load 3rd, 4th and 1st vertex to make a second
            // triangle
            if (is_quad)
            {
                result.indices.push_back(
                    static_cast<unsigned int&&>(get_vertex_id(f3) - 1));

                result.indices.push_back(
                    static_cast<unsigned int&&>(get_vertex_id(f4) - 1));

                result.indices.push_back(
                    static_cast<unsigned int&&>(get_vertex_id(f1) - 1));
            }
        }
    }

    file.close();

    return result;
}

} // namespace pt