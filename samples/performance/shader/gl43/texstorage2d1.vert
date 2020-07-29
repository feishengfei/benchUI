#version 430 core

layout(location=0) in vec2 pos;
layout(location=1) in vec2 coords;
out vec2 texCoords;

void main()
{
    texCoords = coords;
    gl_Position = vec4(pos, 0.0, 1.0);
}
