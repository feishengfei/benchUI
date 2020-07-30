#version 320 es                                  

precision mediump float;

in vec2 v_v2TexCoord;
uniform sampler2D u_s2dTexture;

out vec4 FragColor;

void main()
{
        FragColor = texture(u_s2dTexture, v_v2TexCoord);
}
