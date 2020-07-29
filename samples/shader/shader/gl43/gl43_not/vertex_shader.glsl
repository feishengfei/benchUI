#version   ///GLSL Version 3.20

//uniform float theta;
//uniform int choice;
in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

void main()
{
	bvec2 bc2 = bvec2(1, bool(vPosition.x));
	bvec3 bc3 = bvec3(bc2, 1);
	bvec4 bc4 = bvec4(bc3, 1);

	bvec2 bv2 = not(bc2);
	bvec3 bv3 = not(bc3);
	bvec4 bv4 = not(bc4);

	float average_b = (float(bv2.y) + float(bv3.y) + float(bv4.y)) / 3.0;

	gl_Position = vec4(vPosition.x / 10.0, average_b / 1.0, vPosition.z, 1.0);   
 
	vfColor = vColor;
	gl_PointSize = 8.0;
}
