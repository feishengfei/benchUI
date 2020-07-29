#version  //GLSL Version 3.20; OpenGL es 3.2

precision highp float;
//varying vec4 vfColor;
in vec4 vfColor;
out vec4 FragColor;


void main()
{		
		if(gl_DepthRange.near == 0.0 && gl_DepthRange.far == 1.0)
			FragColor = vec4(0.0, 0.0, 1.0, 0.0);
//			gl_FragColor = vec4(0.0, 0.0, 1.0, 0.0);
		else
			FragColor = vfColor;
//			gl_FragColor = vfColor;
//		gl_FragData[0] = vfColor;
}
