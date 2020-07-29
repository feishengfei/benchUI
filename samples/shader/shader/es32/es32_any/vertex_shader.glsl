#version   ///GLSL Version 3.20

//uniform float theta;
//uniform int choice;
in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

void main()
{
	bvec2 bc2 = bvec2(0, bool(vPosition.x));
	bvec3 bc3 = bvec3(bc2, 0);
	bvec4 bc4 = bvec4(bc3, 0);

	bool bv2 = any(bc2);
	bool bv3 = any(bc3);
	bool bv4 = any(bc4);

	float average_b = (float(bv2) + float(bv3) + float(bv4)) / 3.0;

	gl_Position = vec4(vPosition.x / 10.0, average_b / 1.0, vPosition.z, 1.0);   
 
	vfColor = vColor;
	gl_PointSize = 8.0;
}
