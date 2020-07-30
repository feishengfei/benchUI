#version 430 core

precision mediump int;
precision mediump float;
precision mediump sampler1D;
precision mediump sampler2D;
precision mediump sampler3D;
precision mediump samplerCube;
precision mediump sampler2DArray;
precision mediump samplerBuffer;

uniform mat4 u_m4Projection;
in vec4 a_v4Position;
in vec4 a_v4FontColor;
in vec2 a_v2TexCoord;
out vec4 v_v4FontColor;
out vec2 v_v2TexCoord;
void main()
{
    v_v4FontColor = a_v4FontColor;
    v_v2TexCoord = a_v2TexCoord;
    gl_Position = u_m4Projection * a_v4Position;
}