#version 430 core

precision mediump int;
precision mediump float;
precision mediump sampler1D;
precision mediump sampler2D;
precision mediump sampler3D;
precision mediump samplerCube;
precision mediump sampler2DArray;
precision mediump samplerBuffer;


in vec3 pos;
out vec2 texCoords;

void main()
{
    texCoords = vec2(pos.xy);
    vec4 posv4 = vec4(0.8*pos.xyz, 1.0);
    gl_Position = posv4;
}