/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file basic.vert
 * @author Eric.Ma
 * @par History:
 *    A001: Eric.Ma, 2019-03-29, create file
 * @brief: common vertex shader for vertex*MVP
 *
 */

uniform mat4 u_m4Projection;

attribute vec4 a_v4Position;
attribute vec4 a_v4FillColor;

varying vec4 v_v4FillColor;

void main()
{
    v_v4FillColor = a_v4FillColor;
    gl_Position = u_m4Projection * a_v4Position;
}
