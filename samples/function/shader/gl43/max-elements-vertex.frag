#version 430 core

precision mediump float;

in vec2 v_v2FillColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(v_v2FillColor, 0.5, 1.0);
}

