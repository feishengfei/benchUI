#version 430 core

precision lowp float;

in vec4 vv4colour;
uniform sampler2D u_s2dTexture;

in vec2 v_v2TexCoord;
out vec4 FragColor;

void main()
{
    FragColor = vv4colour*texture(u_s2dTexture, v_v2TexCoord);
}
