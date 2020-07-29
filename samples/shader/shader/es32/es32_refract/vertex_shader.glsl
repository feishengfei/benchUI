#version       ///GLSL Version 3.20

//uniform float theta;
//uniform int choice;
in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

void main()
{
	float eta = vPosition.x;
	vec3 N = vec3(0.0, 1.0, 0.0);
	vec3 I = vec3(1.0, -1.0, 0.0);
	float k = 1.0 - eta * eta * (1.0 - dot(N, I) * dot(N, I));
	vec3 result;
	if (k < 0.0)
    	result = vec3(0.0);
    else
    	result = eta * I - (eta * dot(N, I) + sqrt(k)) * N;

    gl_Position = vec4(refract(I, N, eta) - result, 1.0);

	vfColor = vColor + vec4(0.0, (eta - 1.0) / 0.2 * 0.05, 0.0, 0.0);
	gl_PointSize = 128.0 - (eta - 1.0) / 0.2 * 8.0;
}
