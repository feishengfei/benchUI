#version 430 core
precision mediump float;

in vec3 position;
in vec4 a_vColor;
out vec4 v_vcolor;
void main()
{
    gl_Position =vec4(position,1.0);
    v_vcolor = a_vColor;
}
