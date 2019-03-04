attribute vec3 a_position;
attribute vec2 a_tex_coord;
attribute vec3 a_color;

varying vec4 v_position;
varying vec2 v_tex_coord;
varying vec3 v_color;

uniform mat4 u_transform_matrix;

void main()
{
    v_position  = u_transform_matrix * vec4(a_position, 1.0);
    v_tex_coord = a_tex_coord;
    v_color = a_color;
    gl_Position = v_position;
}