#version 330

attribute vec3 a_position;

uniform mat4 u_transform_matrix;

void main()
{
    gl_Position = u_transform_matrix * vec4(a_position, 1.0);
}