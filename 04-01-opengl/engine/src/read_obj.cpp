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

        // reading triangles (faces)
        if (line[0] == 'f')
        {
            std::stringstream ss(line);

            std::string f1, f2, f3;
            char        garbage;

            ss >> garbage >> f1 >> f2 >> f3;

            result.indices.push_back(get_vertex_id(f1));
            result.indices.push_back(get_vertex_id(f2));
            result.indices.push_back(get_vertex_id(f3));
        }
    }

    file.close();

    return result;
}

} // namespace pt