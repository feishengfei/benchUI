#version 430 core
layout(location=0) in vec2 a_v2Position;
layout(location=1) in vec4 a_v4Color;

out vec4 Color; 

void main()
{
    Color = a_v4Color;
    gl_Position = vec4(a_v2Position, 0.0, 1.0);
}