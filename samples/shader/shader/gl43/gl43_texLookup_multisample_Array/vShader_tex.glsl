#version     //GLSL Version 3.20; OpenGL es 3.2

in vec4 vPosition;
in vec4 vColor;

out vec4 object_color;


void main()
{

	gl_Position = vPosition;
	object_color = vColor;
}
