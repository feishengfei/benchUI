#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;
uniform OFF{
    vec2 off1;
    vec2 off2;
};

out vec4 vocolor;

void main()
{
    off1 = vec2(0.2, -0.2);
    off2 = 0.2 * vPosition.xy;
    vocolor = vColor;
    gl_Position = vPosition + (off1, off2);
}
