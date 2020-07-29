#version 430 core

out vec3 texCoords;
layout(location=0) in vec3 pos;

void main()
{
    texCoords = pos;
    gl_Position = vec4(pos, 1.0);
}

