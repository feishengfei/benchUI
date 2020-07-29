#version 430 core

precision mediump int;
precision mediump float;
precision mediump sampler1D;
precision mediump sampler2D;
precision mediump sampler3D;
precision mediump samplerCube;
precision mediump sampler2DArray;
precision mediump samplerBuffer;


layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

out vec4 vs_fs_color;

void main(void)
{
    vs_fs_color = color;
    gl_Position = position;
}
