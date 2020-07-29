/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from Botson Limited
 * (C) COPYRIGHT 2019 Botson Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from Botson Limited.
 */

#version 100

uniform mat4 mvp;//add
attribute vec4 a_v4Position;
attribute vec2 a_v2TexCoord;

varying vec2 v_v2TexCoord;

void main()
{
    v_v2TexCoord = a_v2TexCoord;
    gl_Position = mvp*a_v4Position;
}