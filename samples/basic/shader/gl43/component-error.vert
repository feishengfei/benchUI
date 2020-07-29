#version 430 core
#extension GL_ARB_enhanced_layouts : enable

precision mediump float;

layout(location=0) in vec4 a_v4Position;
layout(location=1, component=0) out vec2 a;
layout(location=1, component=2) out vec3 b;
void main()
{
    a = a_v4Position.ww;
    b = a_v4Position.xyz;
    gl_Position = a_v4Position;
}
