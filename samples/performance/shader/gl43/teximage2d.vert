#version 430 core

layout(location = 0) in vec3 pos;
out vec2 texCoords;

void main()
{
    texCoords = vec2(pos.xy);
    gl_Position = vec4(pos, 1.0);
}
