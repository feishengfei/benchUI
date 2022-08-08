#version 430 core

layout(depth_unchanged) out float gl_FragDepth;
precision highp float;

in vec4 v_v4FillColor;
out vec4 FragColor;
void main()
{
    FragColor = v_v4FillColor;
}
