#version 430 core

precision mediump float;

in vec4 vert;

void main(void)
{
    gl_Position = vert;
}
