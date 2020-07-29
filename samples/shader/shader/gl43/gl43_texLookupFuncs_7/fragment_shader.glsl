#version    //GLSL Version 3.20; OpenGL es 3.2

precision highp float;
in vec4 vfColor;
//uniform sampler2D texUnit0;

out vec4 FragColor;



void main()
{		
		FragColor = vfColor;
}
