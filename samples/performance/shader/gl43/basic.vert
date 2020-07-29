#version 430 core

layout(location = 0) in vec2 pos;
layout(location = 1) in vec4 vcolor;
out vec4 color;
void main()
{
    color = vcolor;
    gl_Position = vec4(pos, 0.0, 1.0);
}
