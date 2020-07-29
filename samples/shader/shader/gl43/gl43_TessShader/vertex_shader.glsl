#version   ///GLSL Version 3.20

in vec4 vPosition;
in vec4 vColor;

out vec4 vtcColor;



void main()
{
	gl_Position = vPosition;
	vtcColor = vColor;
}

