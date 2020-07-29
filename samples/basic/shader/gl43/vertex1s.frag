#version 430 core

precision mediump float;
in vec4 vcolor;
out vec4 FragColor;
void main()
{
    FragColor = vcolor;
}
