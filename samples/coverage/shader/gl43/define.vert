#version 430 core

#define PI 3.14159265738
#define TIME 2
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;
layout(location = 0) uniform float time;

out vec4 vocolor;

void main()
{
#ifndef TIME
    float angle = degrees(PI * time);
    vocolor = vColor * (sin(angle / 100) + 1.0) / 2;
    gl_Position = vPosition;
#else
    float angle = degrees(TIME * time);
    vocolor = vec4(vColor.x * (cos(angle / 100) + 1.0) / 2, vColor.x * (sin(angle / 100) + 1.0) / 2, 0.0, 1.0);
    gl_Position = vPosition;
#endif
}
