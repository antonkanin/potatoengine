#version 330

uniform vec3 u_color;

void main()
{
    // define the light cube color
    // gl_FragColor = vec4(1.0, 1.0, 1.0, 0);
    gl_FragColor = vec4(u_color, 0);
}