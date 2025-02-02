/*
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 */

#version 100

attribute vec4 a_v4Position;
attribute vec2 a_v2TexCoord;

varying vec2 v_v2TexCoord;
varying vec2 v_v2AlphaCoord;

void main()
{
v_v2TexCoord = a_v2TexCoord * vec2(1.0, 0.5);
v_v2AlphaCoord = v_v2TexCoord + vec2(0.0, 0.5);
    gl_Position = a_v4Position;
}
