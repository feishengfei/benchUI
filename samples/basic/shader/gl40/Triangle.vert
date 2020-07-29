#version 430 core


layout(location = 0) in vec2 vPosition;
layout(location = 1) in vec4 color;
out vec4 vocolor;

void main()
{
    gl_Position = vec4(vPosition, 0.0, 1.0);

    vocolor = color;

}
