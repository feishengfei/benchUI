#version 300 es  
in vec4 a_v4Position;
in float a_PointSize;

void main()
{
    gl_PointSize = a_PointSize;
    gl_Position = a_v4Position;
}
