/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file basic.frag
 * @author Eric.Ma
 * @par History:
 *    A001: Eric.Ma, 2019-03-29, create file
 * @brief: common fragment shader for color transport
 *
 */

precision mediump float;

varying vec4 v_v4FillColor;

void main()
{
    gl_FragColor = v_v4FillColor;
}