#version 430 core

precision mediump float;

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 instance_color;
layout (location = 2) in vec4 instance_position;

out vec4 fragment_color;

void main()
{
    gl_Position = (position + instance_position) * vec4(0.25, 0.25, 1.0, 1.0);
    fragment_color = instance_color;
}
