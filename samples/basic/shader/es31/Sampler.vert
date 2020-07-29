#version 310 es  

layout(location = 0) in vec4 pos_in;
layout(location = 1) in vec4 col_in;
smooth out vec4 col_vary;
void main()
{
	gl_Position = pos_in;
	col_vary = col_in;
}
