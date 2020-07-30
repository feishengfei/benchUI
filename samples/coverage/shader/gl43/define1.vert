#version 430 core

#define SC 2.0

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;
layout(location = 0) uniform float time;

out vec4 vocolor;

void main()
{

#ifdef SC
    float angle = degrees(SC * time);
    vocolor = vec4(vColor.x * (sin(angle / 100) + 1.0) / 2,
         vColor.z * (cos(angle / 100) + 1.0) / 2, 0.5, 1.0);
     gl_Position = vPosition;
     #undef SC
#else
     vocolor = vColor;
     gl_Position = vPosition;
#endif
}
