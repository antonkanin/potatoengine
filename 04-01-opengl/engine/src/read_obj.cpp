#include "read_obj.hpp"
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

    std::vector<vertex>   vertices;
    std::vector<uint16_t> indices;

    std::string line;
    while (getline(file, line))
    {
        if (line.length() == 0)
        {
            continue;
        }

        // reading vertices
        if (line[0] == 'v')
        {
            std::stringstream ss(line);

            float x, y, z;
            char  garbage;

            ss >> garbage >> x >> y >> z;

            vertices.push_back({ x, y, z });
        }

        // reading triangles (faces)
        if (line[0] == 'f')
        {
            std::stringstream ss(line);

            std::string f1, f2, f3;
            char        garbage;

            ss >> garbage >> f1 >> f2 >> f3;

            indices.push_back(get_vertex_id(f1));
            indices.push_back(get_vertex_id(f2));
            indices.push_back(get_vertex_id(f3));
        }
    }

    file.close();

    model result{};

    std::memcpy(result.vertices, vertices.data(), vertices.size());
    result.vert_count = static_cast<unsigned short>(vertices.size());

    std::memcpy(result.indices, indices.data(), indices.size());
    result.ind_count = static_cast<unsigned short>(indices.size());

    return result;
}

}