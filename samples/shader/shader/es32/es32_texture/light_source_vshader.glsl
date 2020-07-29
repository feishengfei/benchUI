#version           ///GLSL Version 3.20

in vec4 vPosition;

void main()
{
	mat4 project = mat4(
					 1,  0, 0, 0,
					 0,  1, 0, 0,
					 0,  0, -1, 0,
					 0,  0, 0, 1
				);
	gl_Position = project * vPosition;
	gl_PointSize = 20.0;
}

//	gl_Position = ry*vPosition;
