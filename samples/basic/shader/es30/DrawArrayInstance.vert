#version 300 es  
precision mediump float;

layout(location = 0) in vec4 a_v4Position;
layout(location = 1) in vec4 offset;

void main()
{
    gl_Position = a_v4Position + offset;
}
