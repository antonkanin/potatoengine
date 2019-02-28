#include "read_obj.hpp"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>

namespace pt
{

struct uv
{
    float u;
    float v;
};

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
    std::string       garbage;
    float             u, v;
    std::stringstream ss(line);

    ss >> garbage >> u >> v;
    texture_uv.push_back({ u, v });
}

void add_face(const std::string& face, const std::vector<uv>& uvs,
              /*OUT*/ std::vector<vertex>&                 vertices,
              /*OUT*/ std::vector<index>&                  indices,
              /*OUT*/ std::set<unsigned int>&              processed_vertex_ids,
              /*OUT*/ std::map<std::string, unsigned int>& vertex_uv_pairs)
{
    const auto slash_pos_1 = face.find('/');

    const auto vertex_id =
        static_cast<unsigned int>(stoi(face.substr(0, slash_pos_1)));

    const auto sub_str = face.substr(slash_pos_1 + 1);

    const auto slash_pos_2 = sub_str.find('/');

    const auto uv_id =
        static_cast<unsigned int>(stoi(sub_str.substr(0, slash_pos_2)));

    const auto vertex_uv_pair_str =
        std::to_string(vertex_id) + std::to_string(uv_id);

    if (processed_vertex_ids.count(vertex_id) == 0)
    {
        processed_vertex_ids.insert(vertex_id);

        vertices[vertex_id - 1].u = uvs[uv_id - 1].u;
        vertices[vertex_id - 1].v = uvs[uv_id - 1].v;

        vertex_uv_pairs[vertex_uv_pair_str] = vertex_id;

        indices.push_back(vertex_id - 1);
    }
    else
    {
        if (vertex_uv_pairs.count(vertex_uv_pair_str) == 0)
        {
            auto vertex_data = vertices[vertex_id - 1];
            vertex_data.u    = uvs[uv_id - 1].u;
            vertex_data.v    = uvs[uv_id - 1].v;

            const auto new_vertex_id =
                static_cast<unsigned int>(vertices.size()) + 1;

            vertex_uv_pairs[vertex_uv_pair_str] = new_vertex_id;

            indices.push_back(new_vertex_id - 1);

            vertices.push_back(vertex_data);

            std::cout << " " << vertices.back().u << ' ' << vertices.back().v;

            std::cout << "   adding vertex " << new_vertex_id;
        }
        else
        {
            const auto new_vertex_id = vertex_uv_pairs.at(vertex_uv_pair_str);
            indices.push_back(new_vertex_id - 1);
        }
    }

    std::cout << std::endl;
}

void read_faces(const std::string& line, const std::vector<uv>& uvs,
                /*OUT*/ std::vector<vertex>&    vertices,
                /*OUT*/ std::vector<index>&     indices,
                /*OUT*/ std::set<unsigned int>& processed_vertex_ids,
                /*OUT*/ std::map<std::string, unsigned int>& vertex_uv_pairs)
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

    // check how many '/' are in the index
    // zero '/' - we only have vertex ID
    // one '/' - we have vertex id and uv id
    // two '/' - vertex, uv id and

    auto slash_count = std::count(begin(f1), end(f1), '/');
    if (0 == slash_count)
    {
        throw std::runtime_error("obj mode not supported");
    }

    // for triangle we  simply load 1st, 2nd, 3rd vertexes
    add_face(f1, uvs, vertices, indices, processed_vertex_ids, vertex_uv_pairs);
    add_face(f2, uvs, vertices, indices, processed_vertex_ids, vertex_uv_pairs);
    add_face(f3, uvs, vertices, indices, processed_vertex_ids, vertex_uv_pairs);

    // if it's a quad we load 3rd, 4th and 1st vertex to make a second
    // triangle
    if (is_quad)
    {
        add_face(f3, uvs, vertices, indices, processed_vertex_ids,
                 vertex_uv_pairs);
        add_face(f4, uvs, vertices, indices, processed_vertex_ids,
                 vertex_uv_pairs);
        add_face(f1, uvs, vertices, indices, processed_vertex_ids,
                 vertex_uv_pairs);
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

    std::set<unsigned int>              processed_vertex_ids;
    std::map<std::string, unsigned int> shifted_vertex_uv_pairs;
    std::vector<uv>                     uvs;

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
            read_uv(line, uvs);
        }

        // reading faces (triangles or quads)
        if (line.substr(0, 2) == "f ")
        {
            read_faces(line, uvs, result.vertices, result.indices,
                       processed_vertex_ids, shifted_vertex_uv_pairs);
        }
    }

    // invert vertical texture coordinate ('V')
    for (auto& v : result.vertices)
    {
        v.v = 1.0f - v.v;
    }

    file.close();

    return result;
}

} // namespace pt