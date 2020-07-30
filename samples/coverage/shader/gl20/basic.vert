#version 430 core
layout(location=0) in vec4 Position;
layout(location=1) in vec4 vFillColor;

out vec4 FillColor;

void main()
{
    FillColor = vFillColor;
    gl_Position = Position;
}
