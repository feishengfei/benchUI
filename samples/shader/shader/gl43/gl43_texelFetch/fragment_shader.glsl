#version  //GLSL Version 3.20; OpenGL es 3.2

precision mediump float;
in vec4 vfColor;
highp uniform samplerBuffer buf;

out vec4 FragColor;



void main()
{		
		if(gl_PointCoord.x < 0.5)
			FragColor = vec4(0.0, 1.0, 0.0, 1.0);
		else
			FragColor = texelFetch(buf, 0) + 0.000001 * vfColor;
}
