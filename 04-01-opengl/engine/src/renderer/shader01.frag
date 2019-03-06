#version 330

varying vec4 v_position;
varying vec2 v_tex_coord;
varying vec3 v_color;
varying vec3 v_normal;

//uniform sampler2D u_texture;
uniform sampler2D texture;
uniform vec3 u_light_pos;

void main()
{
    //gl_FragColor = vec4(v_color, 0);
    vec3 norm = normalize(v_normal);
    vec3 light_dir = normalize(u_light_pos - vec3(v_position));
    float diff = max(dot(norm, light_dir), 0.0) + 0.2;
    //vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);
    //vec3 result = diffuse * v_color;

    gl_FragColor = vec4(v_color, 1.0) * diff;

    //gl_FragColor = texture2D(texture, v_tex_coord) * vec4(v_color, 1.0) * diff;

}