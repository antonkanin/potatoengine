#version 330

attribute vec3 a_position;
attribute vec2 a_tex_coord;
attribute vec3 a_color;
attribute vec3 a_normal;

varying vec4 v_position;
varying vec2 v_tex_coord;
varying vec3 v_color;
varying vec4 v_normal;
varying float v_alpha;
varying float v_instance;

uniform mat4 u_model_view_matrix;
uniform mat4 u_projection_matrix;

void main()
{
    v_position  = u_model_view_matrix * vec4(a_position, 1.0);
    v_tex_coord = a_tex_coord;
    v_color = a_color;
    v_normal = transpose(inverse(u_model_view_matrix)) * vec4(a_normal, 0.0);

    // creting new "shell" with each rendering pass
    v_position += (gl_InstanceID / 200.0) * vec4(normalize(vec3(v_normal)), 0.0);

    v_instance = gl_InstanceID;

    //v_alpha = 1.0 - gl_instance_ID / 5.0;
    v_alpha = 0.5;

    gl_Position = u_projection_matrix * v_position;
}