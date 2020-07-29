#version   ///GLSL Version 4.5

in vec4 vPosition;

void main()
{
    gl_Position = vPosition;
    gl_PointSize = 8.0;
}
