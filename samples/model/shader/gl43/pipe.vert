#version 430 core

layout(location = 0) in vec4 a_position;
void main()
{
   gl_Position = a_position;
}

