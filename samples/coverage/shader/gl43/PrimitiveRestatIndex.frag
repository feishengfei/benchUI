#version 430 core

precision mediump float;
in vec4 v_vcolor;
out vec4 FragColor;
void main()
{
	FragColor = v_vcolor;
}
