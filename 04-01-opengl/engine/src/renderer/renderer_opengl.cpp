#include "renderer_opengl.hpp"
#include "opengl_utils.hpp"
#include "ptm/math.hpp"
#include "ptm/matrix.hpp"
#include "shader.hpp"
#include "triangle.hpp"
#include "vertex.hpp"
#include "program.hpp"

#include <SDL2/SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

namespace pt
{

std::ostream& operator<<(std::ostream& out, const glm::vec4& v)
{
    out << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w;
    return out;
}

glm::vec3 glm_vec(const vec3 vector)
{
    return { vector.x, vector.y, vector.z };
}

glm::mat4x4 glm_mat(const ptm::matrix4x4& mat)
{
    glm::mat4x4 result;

    result[0].x = mat.row1.x;
    result[1].x = mat.row1.y;
    result[2].x = mat.row1.z;
    result[3].x = mat.row1.w;

    result[0].y = mat.row2.x;
    result[1].y = mat.row2.y;
    result[2].y = mat.row2.z;
    result[3].y = mat.row2.w;

    result[0].z = mat.row3.x;
    result[1].z = mat.row3.y;
    result[2].z = mat.row3.z;
    result[3].z = mat.row3.w;

    result[0].w = mat.row4.x;
    result[1].w = mat.row4.y;
    result[2].w = mat.row4.z;
    result[3].w = mat.row4.w;

    return result;
}

glm::mat4x4 look_at(const vec3& position, const vec3& direction, const vec3& up)
{
    return glm::lookAt(glm_vec(position), glm_vec(position + direction),
                       glm_vec(up));
}

void renderer_opengl::update_transform_matrix(
    const transformation& transformation, const camera& camera)
{
    //    glm::vec3 trans_v =
    //        glm::vec3(transformation.position.x, transformation.position.y,
    //                  transformation.position.z);


    ///////////////////////////////////////////////////////////////////////////
    // make translation matrix

    ptm::matrix4x4 translation_m = ptm::translation(transformation.position);

    glm::mat4 translate_m = glm_mat(translation_m);

    ///////////////////////////////////////////////////////////////////////////
    // make rotation matrix

    ptm::matrix4x4 rotation_m = ptm::matrix4x4(ptm::rotation(
        transformation.rotation_angle, transformation.rotation_vector));

//    glm::mat4 rotate_m =
//        glm::rotate(glm::mat4(), transformation.rotation_angle,
//                    glm::vec3(transformation.rotation_vector.x,
//                              transformation.rotation_vector.y,
//                              transformation.rotation_vector.z));

    glm::mat4 rotate_m = glm_mat(rotation_m);

    ///////////////////////////////////////////////////////////////////////////
    // make view matrix

    glm::mat4 view_m =
        look_at(camera.get_position(), camera.get_direction(), camera.get_up());

    ///////////////////////////////////////////////////////////////////////////
    // make projection matrix

    glm::mat4 project_m =
        glm::perspective<float>(glm::pi<float>() / 2, 4.f / 3, 0.1f, 10.0f);

    glm::mat4 full_transfom_m = project_m * view_m * translate_m * rotate_m;

//    GLint transformLoc =
//        glGetUniformLocation(gl_program_id_, "u_transform_matrix");
//    check_gl_errors();
//
//    if (transformLoc == -1)
//    {
//        throw std::runtime_error(
//            "error: could not find attribute 'u_transform_matrix'");
//    }
//
//
//    glUniformMatrix4fv(transformLoc, 1, GL_FALSE,
//                       glm::value_ptr(full_transfom_m));
//    check_gl_errors();

    program_->set_matrix4("u_transform_matrix", glm::value_ptr(full_transfom_m));
}

void renderer_opengl::draw_triangle(const transformation& transformation,
                                    const camera&         camera)
{
    update_transform_matrix(transformation, camera);

    program_->validate();

    glActiveTexture(GL_TEXTURE0);
    check_gl_errors();

    glBindTexture(GL_TEXTURE_2D, texture_id_);
    check_gl_errors();

    glDrawElements(GL_TRIANGLES, indecies_count_, GL_UNSIGNED_INT, nullptr);
    check_gl_errors();
}

bool renderer_opengl::initialize(SDL_Window* window)
{
    using namespace std;

    renderer::initialize(window);

    initialize_gl_functions();

    set_opengl_version();

    if (!get_opengl_context())
    {
        return false;
    }

    program_ = make_unique<program>("shader01.vert", "shader01.frag");
    program_->use();

    glEnable(GL_DEPTH_TEST);
    check_gl_errors();

    return true;
}

void renderer_opengl::swap_buffers()
{
    SDL_GL_SwapWindow(window_);

    glClearColor(0.3f, 0.3f, 1.0f, 0.0f);
    check_gl_errors();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    check_gl_errors();
}

bool renderer_opengl::get_opengl_context()
{
    gl_context_ = SDL_GL_CreateContext(window_);

    if (gl_context_ == nullptr)
    {
        std::cout << "error: count not create OpenGL context: "
                  << SDL_GetError() << '\n';
        return false;
    }

    SDL_assert(gl_context_ != nullptr);

    return true;
}


void renderer_opengl::load_model(const model& model)
{
    glGenVertexArrays(1, &VAO_);
    check_gl_errors();

    glBindVertexArray(VAO_);
    check_gl_errors();

    GLuint VBO;
    glGenBuffers(1, &VBO);
    check_gl_errors();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    check_gl_errors();

    glBufferData(GL_ARRAY_BUFFER, model.vertices.size() * sizeof(vertex),
                 model.vertices.data(), GL_STATIC_DRAW);
    check_gl_errors();

    // position attribute
    glEnableVertexAttribArray(0); // can we use name instead of a number?
    check_gl_errors();

    // TODO replace with reinterpret cast
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
    check_gl_errors();

    // texture coordinates attribute (uv coords)
    glEnableVertexAttribArray(1);
    check_gl_errors();

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex),
                          (void*)(3 * sizeof(float)));
    check_gl_errors();

    ///////////////////////////////////////////////////////////////////////////
    // setting up EBO

    glGenBuffers(1, &EBO_);
    check_gl_errors();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    check_gl_errors();

    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 model.indices.size() * sizeof(unsigned int),
                 model.indices.data(), GL_STATIC_DRAW);

    indecies_count_ = static_cast<GLsizei>(model.indices.size());

    ///////////////////////////////////////////////////////////////////////////
    // loading texture

    //glUseProgram(gl_program_id_);
    //check_gl_errors();
    program_->use();

    int texture_unit = 0;
    glActiveTexture(GL_TEXTURE0 + texture_unit);
    check_gl_errors();

    glGenBuffers(1, &texture_id_);
    check_gl_errors();

    glBindTexture(GL_TEXTURE_2D, texture_id_);
    check_gl_errors();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    check_gl_errors();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    check_gl_errors();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    check_gl_errors();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    check_gl_errors();

    const auto& i = model.image;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(i.width()),
                 static_cast<GLsizei>(i.height()), 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 &i.get_data()[0]);
    check_gl_errors();

    //////////////////////////////////////
    // passing texture to the uniform

//    int location = glGetUniformLocation(gl_program_id_, "u_texture");
//    check_gl_errors();
//
//    assert(-1 != location);
//
//    // http://www.khronos.org/opengles/sdk/docs/man/xhtml/glUniform.xml
//    glUniform1i(location, 0 + texture_unit);
//    check_gl_errors();

    program_->set_1i("u_texture", 0 + texture_unit);

    glEnable(GL_BLEND);
    check_gl_errors();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    check_gl_errors();
}

void renderer_opengl::load_tecture()
{
    // update texture uniform
}

} // namespace pt
