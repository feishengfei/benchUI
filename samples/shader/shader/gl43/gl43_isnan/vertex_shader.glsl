#version   ///GLSL Version 3.20

//uniform float theta;
//uniform int choice;
in ivec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

void main()
{
	bool y1 = isnan(intBitsToFloat(vPosition.y));
	bvec2 y2 = isnan(intBitsToFloat(ivec2(1, vPosition.y)));
	bvec3 y3 = isnan(intBitsToFloat(ivec3(1, 1, vPosition.y)));
	bvec4 y4 = isnan(intBitsToFloat(ivec4(1, 1, 1, vPosition.y)));
	float y_average = 0.25 * (float(y1) + float(y2.y) + float(y3.z) + float(y4.w));

	gl_Position = vec4(float(vPosition.x) / 10.0, y_average / 2.0, float(vPosition.z), 1.0);

	vfColor = vColor;
	gl_PointSize = 8.0;
}
