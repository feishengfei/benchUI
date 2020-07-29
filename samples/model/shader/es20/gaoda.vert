/*
 * This proprietary software may be used only as
 * authorised by a licensing agreement from Botson Limited
 * (C) COPYRIGHT 2019 Botson Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from Botson Limited.
 */

attribute vec4 av4position;
attribute vec3 av3colour;

uniform mat4 mvp;

varying vec3 vv3colour;

void main()
{
	vv3colour = normalize(av3colour);	//¹éÒ»»¯ÑÕÉ«
    //vv3colour = av3colour;
    gl_Position = mvp * av4position;
}
