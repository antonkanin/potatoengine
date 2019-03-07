#version 330

attribute vec3 a_position;
attribute vec2 a_tex_coord;
attribute vec3 a_color;
attribute vec3 a_normal;

varying vec4 v_position;
varying vec2 v_tex_coord;
varying vec3 v_color;
varying vec3 v_normal;

uniform mat4 u_transform_matrix;
//uniform vec3 u_light_pos;

void main()
{
    v_position  = u_transform_matrix * vec4(a_position, 1.0);
    v_tex_coord = a_tex_coord;
    v_color = a_color;
    //v_normal = a_normal;


    v_normal = mat3(transpose(inverse(u_transform_matrix))) * a_normal;
    gl_Position = v_position;

}