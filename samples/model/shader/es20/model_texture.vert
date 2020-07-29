#version 100
precision mediump float;

attribute vec4 a_v4Position;
attribute vec2 a_v2TexCoord;

uniform mat4 mvp;
varying vec2 v_v2TexCoord;

void main()
{
    v_v2TexCoord = a_v2TexCoord;
    gl_Position = mvp * a_v4Position;
}
