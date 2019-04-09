#version 330

varying vec4 v_position;
varying vec2 v_tex_coord;
varying vec3 v_color;
varying vec4 v_normal;
varying float v_instance;
varying float v_shadow;

//uniform sampler2D u_texture;
uniform sampler2D alpha_texture;
uniform sampler2D albedo_texture;
uniform vec3 u_light_pos;
uniform vec3 u_light_direction;
uniform float u_cutoff_angle;

void main()
{
    vec3 norm = normalize(vec3(v_normal));
    vec3 light_dir = normalize(vec3(u_light_pos) - vec3(v_position));
    float ambient = 0.1;
    float diffuse = max(dot(norm, light_dir), 0.0);

    vec3 view_dir = normalize(-1 * vec3(v_position));
    vec3 reflect_dir = reflect(-1 * light_dir, norm);
    float specular = pow(max(dot(view_dir, reflect_dir), 0.0), 256);

    float result_light = ambient + diffuse + specular;
    float alpha = texture2D(alpha_texture, v_tex_coord).r;
    //gl_FragColor = texture2D(albedo_texture, v_tex_coord) * vec4(v_color, alpha) * result_light;
    // gl_FragColor = vec4(v_color, 1.0) * result_light;
    //gl_FragColor = vec4(alpha, 0.0, 0.0, 1.0) * result_light;

    if (v_instance > 0 && alpha < 0.1)
    {
        discard;
    }

    gl_FragColor = texture2D(albedo_texture, v_tex_coord) * vec4(v_color, 1.0) * result_light * v_shadow;
    // gl_FragColor = texture2D(albedo_texture, v_tex_coord);
    //gl_FragColor = vec4(v_color, 1.0) * result_light * v_shadow;

    //gl_FragColor = vec4(alpha, 0.0, 0.0, 1.0) * v_shadow;
}