#version 310 es

precision mediump float;

in vec4 a_vPosition;

void main()
{
    gl_Position = a_vPosition;
}
