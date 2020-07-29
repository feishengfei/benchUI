#version 430 core   //version under 1.4 

precision mediump float;

in vec4 a_v4Position;

void main()
{
    gl_PointSize = 30.0; 
    gl_Position = a_v4Position;
}
