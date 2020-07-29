#version 430 core      

/**
 * @file basic.frag
 * @author Eric.Ma
 * @par History:
 *    A001: Eric.Ma, 2019-03-29, create file
 * @brief: common fragment shader for color transport
 *
 */

precision mediump float;

in vec4 v_v4FillColor;

void main()
{
    gl_FragColor = v_v4FillColor;
}
