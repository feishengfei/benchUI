#version 430 core

layout(depth_greater) out float gl_FragDepth;
precision highp float;

in vec4 v_v4FillColor;
out vec4 FragColor;
void main()
{
    gl_FragDepth = gl_FragCoord.z + 0.1;
    FragColor = v_v4FillColor;
}
