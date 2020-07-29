#version  //GLSL Version 3.20; OpenGL es 3.2

in vec4 vPosition;
in vec4 vColor;
in vec3 vNorm;
uniform float theta;

out vec4 object_color;
out vec4 norm;

void main()
{

	mat4 project = mat4(
					 1,  0, 0, 0,
					 0,  1, 0, 0,
					 0,  0, -1, 0,
					 0,  0, 0, 1
				);
	float angles = radians(theta);
	float c = cos(angles);
	float s = sin(angles);

	mat4 ry = mat4(
					 c,  0, s, 0,
					 0,  1, 0, 0,
					-s,  0, c, 0,
					 0,  0, 0, 1
				);                       //P163
	gl_Position = ry * project * vPosition;
	norm = normalize(ry * project * vec4(vNorm, 0.0));
	object_color = vColor;
}
