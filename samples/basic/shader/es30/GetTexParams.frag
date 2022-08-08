#version 300 es
precision mediump float;

uniform sampler2D u_s2dTexture;

in vec2 v_v2TexCoord;

out vec4 FragColor;

void main()
{
    FragColor = texture2D(u_s2dTexture, v_v2TexCoord);
}
