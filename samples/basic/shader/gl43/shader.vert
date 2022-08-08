#version 430 core

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec4 color;
out vec4 vcolor;
void main()
{
   vcolor = color;
   gl_Position = a_position;
}

