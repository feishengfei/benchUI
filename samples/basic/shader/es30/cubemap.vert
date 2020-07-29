#version 300 es  

in vec4 pos;
in vec3 normal;
out vec3 vnormal;

void main()
{
    vnormal = normal;
    gl_Position = pos;
}
