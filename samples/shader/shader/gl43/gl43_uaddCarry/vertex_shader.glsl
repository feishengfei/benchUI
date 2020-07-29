#version  ///GLSL Version 3.20

//uniform float theta;
//uniform int choice;
in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

uint cal_carry(uint x, uint y)
{
	if((x + y) >= x)
		return 0u;
	else
		return 1u;
}

void main()
{
	highp uint uInteger1 = 0x00000001u;
	highp uint uInteger2 = 0x00000002u;
	highp uint uInteger3 = 0xFFFFFFFEu;
	highp uint uInteger4 = 0xF0000000u;
	lowp uint carry;

	bool a[32];

	a[0] = ((uInteger1 + uInteger2) == uaddCarry(uInteger1, uInteger2, carry));
	a[1] = (cal_carry(uInteger1, uInteger2) == carry);

	a[2] = ((uInteger1 + uInteger3) == uaddCarry(uInteger1, uInteger3, carry));
	a[3] = (cal_carry(uInteger1, uInteger3) == carry);

	a[4] = ((uInteger2 + uInteger3) == uaddCarry(uInteger2, uInteger3, carry));
	a[5] = (cal_carry(uInteger2, uInteger3) == carry);

	a[6] = ((uInteger3 + uInteger4) == uaddCarry(uInteger3, uInteger4, carry));
	a[7] = (cal_carry(uInteger3, uInteger4) == carry);



	lowp uvec2 carry2;
	a[8] = ((uInteger1 + uInteger2) == (uaddCarry(uvec2(1u, uInteger1), uvec2(1u, uInteger2), carry2)).y);
	a[9] = (cal_carry(uInteger1, uInteger2) == carry2.y);

	a[10] = ((uInteger1 + uInteger3) == (uaddCarry(uvec2(1u, uInteger1), uvec2(1u, uInteger3), carry2)).y);
	a[11] = (cal_carry(uInteger1, uInteger3) == carry2.y);

	a[12] = ((uInteger2 + uInteger3) == (uaddCarry(uvec2(1u, uInteger2), uvec2(1u, uInteger3), carry2)).y);
	a[13] = (cal_carry(uInteger2, uInteger3) == carry2.y);

	a[14] = ((uInteger3 + uInteger4) == (uaddCarry(uvec2(1u, uInteger3), uvec2(1u, uInteger4), carry2)).y);
	a[15] = (cal_carry(uInteger3, uInteger4) == carry2.y);



	lowp uvec3 carry3;
	a[16] = ((uInteger1 + uInteger2) == (uaddCarry(uvec3(1u, 1u, uInteger1), uvec3(1u, 1u, uInteger2), carry3)).z);
	a[17] = (cal_carry(uInteger1, uInteger2) == carry3.z);

	a[18] = ((uInteger1 + uInteger3) == (uaddCarry(uvec3(1u, 1u, uInteger1), uvec3(1u, 1u, uInteger3), carry3)).z);
	a[19] = (cal_carry(uInteger1, uInteger3) == carry3.z);

	a[20] = ((uInteger2 + uInteger3) == (uaddCarry(uvec3(1u, 1u, uInteger2), uvec3(1u, 1u, uInteger3), carry3)).z);
	a[21] = (cal_carry(uInteger2, uInteger3) == carry3.z);

	a[22] = ((uInteger3 + uInteger4) == (uaddCarry(uvec3(1u, 1u, uInteger3), uvec3(1u, 1u, uInteger4), carry3)).z);
	a[23] = (cal_carry(uInteger3, uInteger4) == carry3.z);


	lowp uvec4 carry4;
	a[24] = ((uInteger1 + uInteger2) == (uaddCarry(uvec4(1u, 1u, 1u, uInteger1), uvec4(1u, 1u, 1u, uInteger2), carry4)).w);
	a[25] = (cal_carry(uInteger1, uInteger2) == carry4.w);

	a[26] = ((uInteger1 + uInteger3) == (uaddCarry(uvec4(1u, 1u, 1u, uInteger1), uvec4(1u, 1u, 1u, uInteger3), carry4)).w);
	a[27] = (cal_carry(uInteger1, uInteger3) == carry4.w);

	a[28] = ((uInteger2 + uInteger3) == (uaddCarry(uvec4(1u, 1u, 1u, uInteger2), uvec4(1u, 1u, 1u, uInteger3), carry4)).w);
	a[29] = (cal_carry(uInteger2, uInteger3) == carry4.w);

	a[30] = ((uInteger3 + uInteger4) == (uaddCarry(uvec4(1u, 1u, 1u, uInteger3), uvec4(1u, 1u, 1u, uInteger4), carry4)).w);
	a[31] = (cal_carry(uInteger3, uInteger4) == carry4.w);

	gl_Position = vec4(vPosition.x / 16.0, float(a[gl_VertexID]) / 2.0, vPosition.z, 1.0);   

	vfColor = vColor;
	gl_PointSize = 8.0;
}

// 0x10000u = 2^16
// in packUnorm2x16(vec2(vPosition.x, 0.5)), vPosition.x is the lower part, 0.5 is the higher part
