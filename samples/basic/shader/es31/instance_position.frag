#version 310 es                                  

precision mediump float;

in vec4 fragment_color;

out vec4 FragColor;

void main()
{
        FragColor = fragment_color;
}
