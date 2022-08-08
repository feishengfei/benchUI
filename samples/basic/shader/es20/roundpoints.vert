/*
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 */

attribute vec4 a_v4Position;
//attribute vec4 a_v4FillColor;
attribute float a_PointSize;
//uniform bool is_sprite;
//varying vec4 v_v4FillColor;

void main()
{
//    v_v4FillColor = a_v4FillColor;
    gl_Position = a_v4Position;
}
