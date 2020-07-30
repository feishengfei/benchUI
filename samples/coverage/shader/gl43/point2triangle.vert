#version 430 core

layout(location=0) in vec4 aPosition;
layout(location=1) in vec4 aColor;

out VS_OUT{
    vec4 color;
}vs_out;


void main()
{
    vs_out.color = aColor;
    gl_Position = aPosition;
}
