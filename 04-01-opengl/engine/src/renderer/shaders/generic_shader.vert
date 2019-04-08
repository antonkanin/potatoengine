#version 330

attribute vec3 a_position;
attribute vec2 a_tex_coord;
attribute vec3 a_color;
attribute vec3 a_normal;

varying vec4 v_position;
varying vec2 v_tex_coord;
varying vec3 v_color;
varying vec4 v_normal;
varying vec4 v_light_position;

uniform mat4 u_model_view_matrix;
uniform mat4 u_projection_matrix;
uniform vec3 u_light_pos;

void main()
{
    v_position  = u_model_view_matrix * vec4(a_position, 1.0);
    //v_light_position = u_model_view_matrix * vec4(u_light_pos, 1.0);
    v_normal = transpose(inverse(u_model_view_matrix)) * vec4(a_normal, 0.0);

    v_tex_coord = a_tex_coord;
    v_color = a_color;


    v_position += gl_InstanceID * normalize(v_normal);
    gl_Position = u_projection_matrix * v_position;
}