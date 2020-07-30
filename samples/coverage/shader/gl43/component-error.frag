#version 430 core
#extension GL_ARB_enhanced_layouts : enable

precision mediump float;

layout(location=1, component=0) in vec2 a;
layout(location=1, component=2) in vec3 b;
out vec4 FragColor; 

void main()
{
    FragColor = vec4 (a, b.xy);
}
