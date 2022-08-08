#version 430 core

layout(location = 0) in vec4 a_v4Position;
layout(location = 1) in vec4 TexColor;
out vec3 vTexColor;

void main()
{
    vTexColor = TexColor.xyz;
    gl_Position = a_v4Position;
}
