#version 310 es                                  

precision mediump float;
in vec4 a_vPosition;
//in vec4 a_vFillColor;
//out vec4 v_vFillColor;

void main()
{
//    v_vFillColor = a_vFillColor;
    gl_Position = a_vPosition;
}
