#version 430 core

layout(location=0) uniform float time;
layout(location=1) uniform mat4 mvp;

layout(location=0) in vec4 av4position;
layout(location=1) in vec4 color;

out VS_OUT{
    vec4 vv4colour;
    }vs_out;

void main()
{
    vs_out.vv4colour = color;
    gl_Position = mvp * av4position;
}
