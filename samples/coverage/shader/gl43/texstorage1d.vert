#version 430 core

layout(location = 0) in vec3 pos;

void main()
{
    vec4 posv4 = vec4(0.8*pos.xyz, 1.0);
    gl_Position = posv4;
}
