attribute vec3 a_position;
attribute vec2 a_tex_coord;

varying vec4 v_position;
varying vec2 v_tex_coord;

uniform mat4 u_transform_matrix;

void main()
{
    v_position  = u_transform_matrix * vec4(a_position, 1.0);
    v_tex_coord = a_tex_coord;
    gl_Position = v_position;
}