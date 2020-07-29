#version 430 core

layout(location = 0) vec4 pos;
layout(location = 1) vec4 FillColor;
out vec4 v_FillColor;

void main()
{
    v_FillColor = FillColor;
    gl_Position = pos;
}

