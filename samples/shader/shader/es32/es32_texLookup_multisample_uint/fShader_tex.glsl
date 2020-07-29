#version              //GLSL Version 3.20; OpenGL es 3.2

precision highp float;

in flat uvec4 gColor;

out uvec4 FragColor;



void main()
{
		FragColor = gColor;	
}


