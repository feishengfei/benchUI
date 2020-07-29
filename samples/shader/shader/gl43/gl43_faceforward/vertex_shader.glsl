#version  ///GLSL Version 3.20

in vec4 vPosition;
in vec4 vColor;
in vec2 vTexCoord;
in vec3 vNorm;
uniform float theta;

out vec4 object_color;
out vec2 texCoord;
out vec4 norm;
out vec4 object_position;
out vec4 observeDir;



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
	object_position = ry * project * vPosition;
	norm = normalize(ry * project * vec4(vNorm, 0.0));
	vec4 z_negative = project * vec4(0,0,-1,0);

	norm = faceforward(norm, z_negative, norm);

	object_color = vColor;
	texCoord = vTexCoord;
	gl_Position = object_position;
	observeDir = normalize(project * vec4(0.0, 0.0, -1.0, 1.0));
}
