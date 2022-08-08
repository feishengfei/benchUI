#version 430 core           

/**
 * @file basic.vert
 * @author Eric.Ma
 * @par History:
 *    A001: Eric.Ma, 2019-03-29, create file
 * @brief: common vertex shader for vertex*MVP
 *
 */

//uniform mat4 u_m4Projection;

in vec4 a_v4Position;
in vec4 a_v4FillColor;
out vec4 v_v4FillColor;

void main()
{
    v_v4FillColor = a_v4FillColor;
    gl_Position = a_v4Position;
//    gl_Position = u_m4Projection * a_v4Position;
}
