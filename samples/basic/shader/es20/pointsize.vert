/*
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 */

attribute vec4 a_v4Position;
attribute float a_PointSize;
varying vec4 v_v4FillColor;

void main()
{
    gl_Position = a_v4Position;
    gl_PointSize = a_PointSize;
}
