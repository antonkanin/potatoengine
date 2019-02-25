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

void read_vertices(const std::string&           line,
                   /*OUT*/ std::vector<vertex>& vertices)
{
    std::stringstream ss(line);

    float x, y, z;
    char  garbage;

    ss >> garbage >> x >> y >> z;

    vertices.push_back({ x, y, z });
}

void read_uv(const std::string& line, std::vector<uv>& texture_uv)
{
    // read texture coordinates
}

void read_faces(const std::string& line, const std::vector<vertex/*OUT*/ std::vector<index>& indices)
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
    indices.push_back(static_cast<unsigned int&&>(get_vertex_id(f1) - 1));

    indices.push_back(static_cast<unsigned int&&>(get_vertex_id(f2) - 1));

    indices.push_back(static_cast<unsigned int&&>(get_vertex_id(f3) - 1));

    // if it's a quad we load 3rd, 4th and 1st vertex to make a second
    // triangle
    if (is_quad)
    {
        indices.push_back(static_cast<unsigned int&&>(get_vertex_id(f3) - 1));

        indices.push_back(static_cast<unsigned int&&>(get_vertex_id(f4) - 1));

        indices.push_back(static_cast<unsigned int&&>(get_vertex_id(f1) - 1));
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

    // get total vertex count in the obj file

    // when reading faces
    //   check if the face is already in the set
    //      if it is -> get a next available number from the vertex count and add new vertex with the same coords and UV value
    //

    std::string line;
    while (getline(file, line))
    {
        if (line.length() == 0)
        {
            continue;
        }

        // reading vertices
        if (line.substr(0, 2) == "v ")
        {
            read_vertices(line, result.vertices);
        }

        // reading UVs
        if (line.substr(0, 2) == "vt")
        {
            read_uv(line, result.texture_uv);
        }

        // reading faces (triangles or quads)
        if (line.substr(0, 2) == "f")
        {
            read_faces(line, result.indices);
        }
    }

    file.close();

    return result;
}

} // namespace pt