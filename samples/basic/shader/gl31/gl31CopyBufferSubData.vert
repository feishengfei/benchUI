#version 430 core
layout(location = 0) in vec4 pos;

out vec4 vcolor;

void main()
{
    gl_Position = pos;
}
