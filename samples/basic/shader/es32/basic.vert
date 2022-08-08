#version 320 es                                  

precision mediump float;

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

out vec4 fragment_color;

void main()
{
    gl_Position = position;
    fragment_color = color;
}
