#version 310 es                                  

precision mediump float;

layout(location = 0) in vec4 a_v4Position;
layout(location = 1) in vec4 a_v4Color;
out vec4 v_v4Color;
void main()
{
    v_v4Color = a_v4Color;
    gl_Position = a_v4Position;
}
