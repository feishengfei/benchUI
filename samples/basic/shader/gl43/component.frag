#version 430 core

precision mediump float;

layout(location=1, component=0) in float a;
layout(location=1, component=1) in vec3 b;
out vec4 FragColor; 

void main()
{
    FragColor = vec4 (a, b);
}
