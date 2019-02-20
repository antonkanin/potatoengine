varying vec4  v_position;
uniform float u_wave_value;

void main()
{
    float r = abs(v_position.x * 2.0);
    // float r = 0.0;
    float g = v_position.y * 2.0;

    // float g = 1.0;
    float b      = 0.0;
    gl_FragColor = vec4(r, g, b, 0);
}