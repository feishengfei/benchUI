#version 430 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex;
smooth out vec2 texCoords;
void main()
{
    texCoords = tex;
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
}
