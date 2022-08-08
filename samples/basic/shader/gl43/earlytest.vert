#version 430 core

layout(location=0) in vec4 a_v4Position;

void main()
{
    gl_Position = a_v4Position;
}
