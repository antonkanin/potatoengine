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
uniform vec3 u_light_direction; // normalized light direction
uniform float u_light_angle;

void main()
{
    float alpha = texture2D(alpha_texture, v_tex_coord).r;

    if (v_instance > 0 && alpha < 0.1)
    {
        discard;
    }

    vec3 s = normalize(vec3(v_position) - u_light_pos);
    float angle = acos(dot(s, normalize(u_light_direction)));

    float ambient = 0.25;

    if (angle <= u_light_angle)
    {
        vec3 norm = normalize(vec3(v_normal));

        vec3 light_dir = normalize(vec3(u_light_pos) - vec3(v_position));

        float diffuse = max(dot(norm, light_dir), 0.0);

        vec3 view_dir = normalize(-1 * vec3(v_position));
        vec3 reflect_dir = reflect(-1 * light_dir, norm);
        float specular = pow(max(dot(view_dir, reflect_dir), 0.0), 256);

        float result_light = ambient + 2.0 * diffuse + specular;

        gl_FragColor = texture2D(albedo_texture, v_tex_coord) * vec4(v_color, 1.0) * result_light * v_shadow;
    }
    else
    {
        gl_FragColor = texture2D(albedo_texture, v_tex_coord) * vec4(v_color, 1.0) * ambient * v_shadow;
    }
}