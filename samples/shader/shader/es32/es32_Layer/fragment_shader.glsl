#version  //GLSL Version 3.20; OpenGL es 3.2

precision highp float;

in vec4 gColor;

out vec4 FragColor;



void main()
{
//		if(gl_Layer == 1)
//			discard;
		FragColor = gColor;	
}


