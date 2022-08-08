#version 430 core

layout(location = 0) in vec2 aPos;
layout(location = 0) uniform mat2x2 pos;
void main()
{
    gl_Position = vec4(aPos.x + pos[0][0], aPos.y + pos[1][0], 0.0, 1.0);
}
