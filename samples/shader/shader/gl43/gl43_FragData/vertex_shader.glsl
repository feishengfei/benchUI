#version      ///GLSL Version 2.0
//attribute vec4 vPosition;
//attribute vec4 vColor;
in vec4 vPosition;
in vec4 vColor;

//varying vec4 vfColor;
out vec4 vfColor;




void main()
{
	gl_Position = vec4(vPosition.x / 16.0, 0.0 / 2.0, vPosition.z, 1.0);
	vfColor = vColor;
	gl_PointSize = 8.0;
}
