#version 430 core

layout(location = 0) in vec4 a_v4Position;
layout(location = 1) in vec4 acolor;
out vec4 vcolor;
void main()
{
    vcolor = acolor;
    gl_Position = a_v4Position;
}
