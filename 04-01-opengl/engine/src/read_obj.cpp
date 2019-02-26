#include "read_obj.hpp"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <map>
#include <set>
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
    std::string       garbage;
    float             u, v;
    std::stringstream ss(line);

    ss >> garbage >> u >> v;
    texture_uv.push_back({ u, v });
}

struct face
{
    int vertex_id;
    int uv_id;
    int normal_id;
};

void add_face(const std::string& face, std::vector<vertex>& vertices,
              std::vector<index>&                  indices,
              std::set<unsigned int>&              processed_vertex_ids,
              std::map<std::string, unsigned int>& vertex_uv_pairs)
{

    auto slash_pos = face.find('/');

    auto vertex_id = static_cast<unsigned int>(stoi(face.substr(0, slash_pos)));
    auto uv_id     = static_cast<unsigned int>(
        stoi(face.substr(slash_pos, face.length() - slash_pos)));

    auto vertex_uv_pair_str = std::to_string(vertex_id) + std::to_string(uv_id);

    /*
        if (vertex_is is NOT in the processed_vertices)
        {
            add vertex to the processed_vertices
            add vertex_id to the list of indecies
            add vert_uv paur to the map with the value = vertex_id
        }
        else
        {
            if (pair is not in the list of UV pairs)
            {
                // generating new vertex
                get vertex data using vertex_id from the vertex list
                                                                and add new
                vertex the list of vertices use the count of vertices as the new
                vertex_id add old_vertex_id/uv pair to the list of pairs and
       link them to the new_vertex_idf add new_vertex_id to the list of indices
       add new vertex data to the list of vertices (create a copy)
            }
            else
            {
                get a vertex_id code form the pair
                add this code ad a new vertex to the list of indices
            }
        }
    */

    if (processed_vertex_ids.count(vertex_id) == 0)
    {
        processed_vertex_ids.insert(vertex_id);
        vertex_uv_pairs[vertex_uv_pair_str] = vertex_id;

        indices.push_back(vertex_id - 1);
    }
    else
    {
        if (vertex_uv_pairs.count(vertex_uv_pair_str) == 0)
        {
            const auto vertex_data = vertices[vertex_id - 1];
            const auto new_vertex_id =
                static_cast<unsigned int>(vertices.size());

            vertex_uv_pairs[vertex_uv_pair_str] = new_vertex_id;

            indices.push_back(new_vertex_id - 1);
            vertices.push_back(vertex_data);
        }
        else
        {
            const auto new_vertex_id = vertex_uv_pairs.at(vertex_uv_pair_str);

            indices.push_back(new_vertex_id - 1);
        }
    }
}

void read_faces(const std::string& line, std::vector<vertex>& vertices,
                /*OUT*/ std::vector<index>& indices,
                /*OUT*/ std::set<unsigned int>&              processed_vertex_ids,
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
    if (0 == slash_count || 2 == slash_count)
    {
        throw std::runtime_error("obj mode not supported");
    }

    // for triangle we  simply load 1st, 2nd, 3rd vertexes
    add_face(f1, vertices, indices, processed_vertex_ids, vertex_uv_pairs);
    add_face(f2, vertices, indices, processed_vertex_ids, vertex_uv_pairs);
    add_face(f3, vertices, indices, processed_vertex_ids, vertex_uv_pairs);

    // if it's a quad we load 3rd, 4th and 1st vertex to make a second
    // triangle
    if (is_quad)
    {
        add_face(f3, vertices, indices, processed_vertex_ids, vertex_uv_pairs);
        add_face(f4, vertices, indices, processed_vertex_ids, vertex_uv_pairs);
        add_face(f1, vertices, indices, processed_vertex_ids, vertex_uv_pairs);
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
        if (line.substr(0, 2) == "f ")
        {
            read_faces(line, result.vertices, result.indices, processed_vertex_ids, shifted_vertex_uv_pairs);
        }
    }

    file.close();

    return result;
}

} // namespace pt