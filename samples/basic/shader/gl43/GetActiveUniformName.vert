#version 430 core 
layout(location=0) in vec3 position;
layout(location=1) in vec4 acolor;
layout(location=0) uniform float u1f;
layout(location=1) uniform vec2 u2f;
layout(location=2) uniform vec3 u3f;
layout(location=3) uniform vec4 u4f;
out vec4 vcolor;
void main()
{
    vcolor = acolor + u4f;
    float x = position.x + u1f + u2f.x + u3f.x;
    float y = position.y + u2f.y + u3f.y;
    float z = position.z + u3f.z;
    gl_Position = vec4(x, y, z, 1.0);
} 

