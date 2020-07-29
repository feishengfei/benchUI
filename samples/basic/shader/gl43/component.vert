#version 430 core

precision mediump float;

layout(location=0) in vec4 a_v4Position;
layout(location=1, component=0) out float a;
layout(location=1, component=1) out vec3 b;
void main()
{
    a = a_v4Position.w;
    b = a_v4Position.xyz;
    gl_Position = a_v4Position;
}
