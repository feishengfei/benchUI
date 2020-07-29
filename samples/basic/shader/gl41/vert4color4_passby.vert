#version 430 core

in vec4 a_v4Color;
in vec4 a_v4Position;
out vec4 Color; 

void main()
{
    Color = a_v4Color;
    gl_Position = a_v4Position;
}
