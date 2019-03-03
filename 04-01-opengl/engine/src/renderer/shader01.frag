//varying vec4 v_position;
varying vec2 v_tex_coord;

//uniform sampler2D u_texture;
uniform sampler2D texture;

void main()
{
    //gl_FragColor = vec4(0, 0, 1, 0);
    gl_FragColor = texture2D(texture, v_tex_coord);
}