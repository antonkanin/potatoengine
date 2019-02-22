attribute vec3 a_position;
varying vec4 v_position;
uniform mat4 u_transform_matrix;

void main()
{
    v_position  = u_transform_matrix * vec4(a_position, 1.0);
    gl_Position = v_position;
}