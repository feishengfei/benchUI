#version 430 core

layout(location = 0) in vec4 a_v4Position;
layout(location = 1) in ivec4 acolor;
out vec4 vcolor;
void main()
{
    float a = float(acolor.r);
    float b = float(acolor.g);
    float c = float(acolor.b);
    float d = float(acolor.a);
    vcolor = vec4(a, b, c, d);
    gl_Position = a_v4Position;
}
