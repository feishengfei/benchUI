#version 430 core

in vec3 pos;
out vec2 texCoords;

void main()
{
    texCoords = vec2(pos.xy);
    vec4 posv4 = vec4(0.8*pos.xyz, 1.0);
    gl_Position = posv4;
}
