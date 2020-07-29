#version              //GLSL Version 3.20; OpenGL es 3.2

precision highp float;

in flat ivec4 gColor;

out ivec4 FragColor;



void main()
{
		FragColor = gColor;	
}


