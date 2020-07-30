#version 310 es                                  

precision mediump float;

uniform vec4 v_vFillColor;
out vec4 Color;

void main()
{
    Color = v_vFillColor;
}
