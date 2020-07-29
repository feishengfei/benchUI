#version 320 es                                  

precision mediump float;

in vec4 a_v4Position;
in vec2 a_v2TexCoord;

out vec2 v_v2TexCoord;

void main()
{
    v_v2TexCoord = a_v2TexCoord;
    gl_Position = a_v4Position;
}
