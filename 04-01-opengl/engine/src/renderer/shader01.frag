//varying vec4 v_position;
varying vec2 v_tex_coord;
varying vec3 v_color;

//uniform sampler2D u_texture;
uniform sampler2D texture;

void main()
{
    gl_FragColor = vec4(v_color, 0);
    //gl_FragColor = texture2D(texture, v_tex_coord) * vec4(v_color, 1.0);
}