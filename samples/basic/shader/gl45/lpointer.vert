#version 430 core

precision mediump int;
precision mediump float;
precision mediump sampler1D;
precision mediump sampler2D;
precision mediump sampler3D;
precision mediump samplerCube;
precision mediump sampler2DArray;
precision mediump samplerBuffer;


layout(location = 0) in vec4 pos;
layout(location = 1) in dvec2 col;

out vec4 uColor;

void main()
{
    uColor = vec4(col, 0.0, 1.0);
    gl_Position = pos;
}

