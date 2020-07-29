#version 310 es  
precision mediump float;

in vec4 piglit_vertex;

void main()
{
    gl_Position = piglit_vertex;
}
