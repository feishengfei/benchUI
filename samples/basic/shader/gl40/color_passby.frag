#version 430 core
precision mediump float;

in vec4 Color; 
layout(location = 0) out vec4 FragColor;

void main()
{
    FragColor = Color;
}