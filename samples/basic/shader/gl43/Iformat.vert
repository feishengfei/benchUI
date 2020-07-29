#version 430 core

layout(location = 0) in ivec3 vPosition;

out vec4 vcolor;

void main()
{
    float a = float(vPosition.x)/1000;
    float b = float(vPosition.y)/1000;
    gl_Position = vec4(a, b, 0.0, 1.0);

}
