/*
 * This proprietary software may be used only as
 * authorised by a licensing agreement from Botson Limited
 * (C) COPYRIGHT 2019 Botson Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from Botson Limited.
 */

precision lowp float;

varying vec4 vv4colour;
uniform sampler2D u_s2dTexture;

varying vec2 v_v2TexCoord;
void main()
{
    gl_FragColor = vv4colour*texture2D(u_s2dTexture, v_v2TexCoord);
}
