#version 430 core
precision mediump float;

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 a_vColor;
out vec4 v_vcolor;
void main()
{
    gl_Position =position;
    v_vcolor = a_vColor;
}
