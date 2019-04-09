#version 330

attribute vec3 a_position;
attribute vec2 a_tex_coord;
attribute vec3 a_color;
attribute vec3 a_normal;

varying vec4 v_position;
varying vec2 v_tex_coord;
varying vec3 v_color;
varying vec4 v_normal;
varying float v_instance;
varying float v_shadow;

uniform mat4 u_model_view_matrix;
uniform mat4 u_projection_matrix;
uniform vec3 u_gravity;

void main()
{
    v_position  = u_model_view_matrix * vec4(a_position, 1.0);
    v_tex_coord = a_tex_coord;
    v_color = a_color;
    v_normal = transpose(inverse(u_model_view_matrix)) * vec4(a_normal, 0.0);

    // creting new "shell" with each rendering pass
    v_position += (gl_InstanceID / 200.0) * vec4(normalize(vec3(v_normal)) + u_gravity * gl_InstanceID, 0.0);

    float max_value = gl_InstanceID / 64.0;
    v_shadow = mix(0.2, 1.0, max_value);
    //v_shadow = 1.0;

    v_instance = gl_InstanceID;

    gl_Position = u_projection_matrix * v_position;
}