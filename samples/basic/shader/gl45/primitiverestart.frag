#version 430 core

precision mediump int;
precision mediump float;
precision mediump sampler1D;
precision mediump sampler2D;
precision mediump sampler3D;
precision mediump samplerCube;
precision mediump sampler2DArray;
precision mediump samplerBuffer;


in vec4 vs_fs_color;

layout (location = 0) out vec4 color;

void main(void)
{
    color = vs_fs_color;
}
