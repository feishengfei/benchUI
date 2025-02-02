/*
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 */

#version 100

attribute vec4 a_v4Position;
attribute vec2 a_v2TexCoord;

varying vec2 v_v2TexCoord;

void main()
{
    v_v2TexCoord = a_v2TexCoord;
    gl_Position = a_v4Position;
}