#version 430 core
precision highp float;

in vec2 a_v2Position;

void main()
{
    gl_Position = vec4(a_v2Position, 0.0, 1.0);
}
