#version

//uniform float theta;
//uniform int choice;
in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

uint cal_borrow(uint x, uint y)
{
	if(x >= y)
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
	lowp uint borrow;

	bool a[32];

	a[0] = ((uInteger1 - uInteger2) == usubBorrow(uInteger1, uInteger2, borrow));
	a[1] = (cal_borrow(uInteger1, uInteger2) == borrow);

	a[2] = ((uInteger1 - uInteger3) == usubBorrow(uInteger1, uInteger3, borrow));
	a[3] = (cal_borrow(uInteger1, uInteger3) == borrow);

	a[4] = ((uInteger2 - uInteger3) == usubBorrow(uInteger2, uInteger3, borrow));
	a[5] = (cal_borrow(uInteger2, uInteger3) == borrow);

	a[6] = ((uInteger3 - uInteger4) == usubBorrow(uInteger3, uInteger4, borrow));
	a[7] = (cal_borrow(uInteger3, uInteger4) == borrow);



	lowp uvec2 borrow2;
	a[8] = ((uInteger1 - uInteger2) == (usubBorrow(uvec2(1u, uInteger1), uvec2(1u, uInteger2), borrow2)).y);
	a[9] = (cal_borrow(uInteger1, uInteger2) == borrow2.y);

	a[10] = ((uInteger1 - uInteger3) == (usubBorrow(uvec2(1u, uInteger1), uvec2(1u, uInteger3), borrow2)).y);
	a[11] = (cal_borrow(uInteger1, uInteger3) == borrow2.y);

	a[12] = ((uInteger2 - uInteger3) == (usubBorrow(uvec2(1u, uInteger2), uvec2(1u, uInteger3), borrow2)).y);
	a[13] = (cal_borrow(uInteger2, uInteger3) == borrow2.y);

	a[14] = ((uInteger3 - uInteger4) == (usubBorrow(uvec2(1u, uInteger3), uvec2(1u, uInteger4), borrow2)).y);
	a[15] = (cal_borrow(uInteger3, uInteger4) == borrow2.y);



	lowp uvec3 borrow3;
	a[16] = ((uInteger1 - uInteger2) == (usubBorrow(uvec3(1u, 1u, uInteger1), uvec3(1u, 1u, uInteger2), borrow3)).z);
	a[17] = (cal_borrow(uInteger1, uInteger2) == borrow3.z);

	a[18] = ((uInteger1 - uInteger3) == (usubBorrow(uvec3(1u, 1u, uInteger1), uvec3(1u, 1u, uInteger3), borrow3)).z);
	a[19] = (cal_borrow(uInteger1, uInteger3) == borrow3.z);

	a[20] = ((uInteger2 - uInteger3) == (usubBorrow(uvec3(1u, 1u, uInteger2), uvec3(1u, 1u, uInteger3), borrow3)).z);
	a[21] = (cal_borrow(uInteger2, uInteger3) == borrow3.z);

	a[22] = ((uInteger3 - uInteger4) == (usubBorrow(uvec3(1u, 1u, uInteger3), uvec3(1u, 1u, uInteger4), borrow3)).z);
	a[23] = (cal_borrow(uInteger3, uInteger4) == borrow3.z);


	lowp uvec4 borrow4;
	a[24] = ((uInteger1 - uInteger2) == (usubBorrow(uvec4(1u, 1u, 1u, uInteger1), uvec4(1u, 1u, 1u, uInteger2), borrow4)).w);
	a[25] = (cal_borrow(uInteger1, uInteger2) == borrow4.w);

	a[26] = ((uInteger1 - uInteger3) == (usubBorrow(uvec4(1u, 1u, 1u, uInteger1), uvec4(1u, 1u, 1u, uInteger3), borrow4)).w);
	a[27] = (cal_borrow(uInteger1, uInteger3) == borrow4.w);

	a[28] = ((uInteger2 - uInteger3) == (usubBorrow(uvec4(1u, 1u, 1u, uInteger2), uvec4(1u, 1u, 1u, uInteger3), borrow4)).w);
	a[29] = (cal_borrow(uInteger2, uInteger3) == borrow4.w);

	a[30] = ((uInteger3 - uInteger4) == (usubBorrow(uvec4(1u, 1u, 1u, uInteger3), uvec4(1u, 1u, 1u, uInteger4), borrow4)).w);
	a[31] = (cal_borrow(uInteger3, uInteger4) == borrow4.w);

	gl_Position = vec4(vPosition.x / 16.0, float(a[gl_VertexID]) / 2.0, vPosition.z, 1.0);   

	vfColor = vColor;
	gl_PointSize = 8.0;
}

// 0x10000u = 2^16
// in packUnorm2x16(vec2(vPosition.x, 0.5)), vPosition.x is the lower part, 0.5 is the higher part
