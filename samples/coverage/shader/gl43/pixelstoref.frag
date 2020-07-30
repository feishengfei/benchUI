#version 430 core

precision mediump int;
precision mediump float;

precision mediump sampler2D;
precision mediump sampler3D;
precision mediump samplerCube;
precision mediump sampler2DArray;
precision mediump samplerBuffer;


uniform sampler2D u_s2dTexture;

in vec2 v_v2TexCoord;
out vec4 FragColor;
void main()
{
    FragColor = texture(u_s2dTexture, v_v2TexCoord);
}