#version 300 es  
precision mediump float;
in vec4 a_v4Position;
in vec4 offset;
void main()
{
    gl_Position = a_v4Position + offset;
}
