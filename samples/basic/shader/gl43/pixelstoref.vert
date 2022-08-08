#version 430 core

precision mediump int;
precision mediump float;

precision mediump sampler2D;
precision mediump sampler3D;
precision mediump samplerCube;
precision mediump sampler2DArray;
precision mediump samplerBuffer;


layout(location = 0) in vec4 a_v4Position;
layout(location = 1) in vec2 a_v2TexCoord;

out vec2 v_v2TexCoord;

void main()
{
    v_v2TexCoord = a_v2TexCoord;
    gl_Position = a_v4Position;
}