#version 330

varying vec4 v_position;
varying vec2 v_tex_coord;
varying vec3 v_color;
varying vec3 v_normal;
varying vec4 v_light_position;

//uniform sampler2D u_texture;
uniform sampler2D texture;

void main()
{
    vec3 norm = normalize(v_normal);
    vec3 light_dir = normalize(vec3(v_light_position) - vec3(v_position));
    float diff = max(dot(norm, light_dir), 0.1) + 0.1;
    gl_FragColor = vec4(v_color, 1.0) * diff;


    //vec3 t = normalize(u_light_pos);
    //gl_FragColor = vec4(t.x, 0.0, 0.0, 1.0);
    //gl_FragColor = vec4(v_color, 1.0) * diff;

    //vec3 l = normalize(v_light_position.xyz);

    //gl_FragColor = vec4(diff, 0.0, 0.0, 1.0);
    //gl_FragColor = vec4(l.x, 0.0, 0.0, 1.0);

    //gl_FragColor = texture2D(texture, v_tex_coord) * vec4(v_color, 1.0) * diff;

}