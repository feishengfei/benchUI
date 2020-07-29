#version 430 core

precision mediump int;
precision mediump float;
precision mediump sampler1D;
precision mediump sampler2D;
precision mediump sampler3D;
precision mediump samplerCube;
precision mediump sampler2DArray;
precision mediump samplerBuffer;


layout(location = 0) in vec3 pos;

void main()
{
    vec4 posv4 = vec4(0.8*pos.xyz, 1.0);
    gl_Position = posv4;
}
