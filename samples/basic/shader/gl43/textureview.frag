#version 430 core

precision mediump float;

uniform sampler2D u_s2dTexture;

in vec2 v_v2TexCoord;

out vec4 FragColor;
void main()
{
   FragColor = texture(u_s2dTexture, v_v2TexCoord);
}