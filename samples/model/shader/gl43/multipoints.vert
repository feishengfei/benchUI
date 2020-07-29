#version 430 core

layout(location = 0) in vec2 vPosition;
layout(location = 1) in float pointsize;

void main()
{
    gl_PointSize = pointsize;
    gl_Position = vec4(vPosition, 0.0, 1.0);
}
