#pragma once

#include <vector>

#include "opengl_utils.hpp"
#include "vertex.hpp"

namespace pt
{

class vb_builder
{
public:
    virtual void register_vertices(std::vector<vertex> vertices,
                              std::vector<int>    indices) = 0;
};

class vb_builder_opengl : public vb_builder
{
public:
    virtual void register_vertices(std::vector<vertex> vertices,
                              std::vector<int>  indices)
    {
        unsigned int VBO = 0;
        unsigned int EBO = 0;

        ///////////////////////////////////////////////////////////////////////////
        // generate buffers
        glGenVertexArrays(1, &VAO_);
        check_gl_errors();

        glGenBuffers(1, &VBO);
        check_gl_errors();

        glGenBuffers(1, &EBO);
        check_gl_errors();

        ///////////////////////////////////////////////////////////////////////////
        // bind buffers

        glBindVertexArray(VAO_);
        check_gl_errors();

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        check_gl_errors();

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex),
                     vertices.data(), GL_STATIC_DRAW);
        check_gl_errors();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        check_gl_errors();

        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     indices.size() * sizeof(unsigned int), indices.data(),
                     GL_STATIC_DRAW);
        check_gl_errors();

        ///////////////////////////////////////////////////////////////////////////
        // setup attributes

        // position
        glEnableVertexAttribArray(0); // can we use name instead of a number?
        check_gl_errors();

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex),
                              (void*)0);
        check_gl_errors();

        // texture
        glEnableVertexAttribArray(1);
        check_gl_errors();

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex),
                              (void*)(sizeof(ptm::vec3)));
        check_gl_errors();

        // color
        glEnableVertexAttribArray(2);
        check_gl_errors();

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex),
                              (void*)(sizeof(ptm::vec3) + sizeof(ptm::vec2)));
        check_gl_errors();

        // normals
        glEnableVertexAttribArray(3);
        check_gl_errors();

        glVertexAttribPointer(
            3, 3, GL_FLOAT, GL_FALSE, sizeof(vertex),
            (void*)(sizeof(ptm::vec3) + sizeof(ptm::vec2) + sizeof(ptm::vec3)));
        check_gl_errors();

        glBindVertexArray(0);
        check_gl_errors();
    };

private:
    unsigned int VAO_ = 0;
};

}