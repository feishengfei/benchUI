#version 430 core

in vec4 a_v4Color;
in vec2 a_v2Position;
out vec4 Color; 

void main()
{
    Color = a_v4Color;
    gl_Position = vec4(a_v2Position, 0.0, 1.0);
}
