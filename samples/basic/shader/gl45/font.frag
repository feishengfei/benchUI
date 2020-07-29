#version 430 core

precision mediump int;
precision mediump float;
precision mediump sampler1D;
precision mediump sampler2D;
precision mediump sampler3D;
precision mediump samplerCube;
precision mediump sampler2DArray;
precision mediump samplerBuffer;

uniform sampler2D u_s2dTexture;
in vec2 v_v2TexCoord;
in vec4 v_v4FontColor;

out vec4 FragColor;
void main()
{
    vec4 v4Texel = texture2D(u_s2dTexture, v_v2TexCoord);
    FragColor = v_v4FontColor * v4Texel;
}