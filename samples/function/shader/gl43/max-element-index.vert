#version 430 core

#pragma debug(on)

precision mediump float;

uniform mat4 u_m4Projection;

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aColor;

out vec2 v_v2FillColor;

void main()
{
    v_v2FillColor = aColor;
    gl_PointSize = 10.0;
    gl_Position =  vec4(aPos, 1.0, 1.0);
}
