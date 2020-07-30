#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;

layout(std140, row_major) uniform MVP {
    mat4 rotate;
    mat4 scale;
    mat4 translation;
};

out vec4 vocolor;

void main()
{
    mat4 vMVP = scale * rotate * translation;
    gl_Position = vMVP * vPosition ;
    vocolor = vColor;
}
