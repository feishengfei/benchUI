#version                //GLSL Version 3.20; OpenGL es 3.2

layout(location = 0) in vec4 vPosition;
layout(location = 1) in ivec4 vColor;

flat out ivec4 object_color;


void main()
{

	gl_Position = vPosition;
	object_color = vColor;
}
