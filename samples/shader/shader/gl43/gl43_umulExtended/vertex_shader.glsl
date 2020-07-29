#version

//uniform float theta;
//uniform int choice;
in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

uint low(uint x)
{
	return (x & 0x0000FFFFu);
}

uint high(uint x)
{
	return ((x >> 16) & 0x0000FFFFu);
}

highp uint umExtended_H(highp uint uInteger1, highp uint uInteger2)
{
	lowp uint carry = 0u;


	highp uint result_high = 0u;
	highp uint result_low = 0u;

	result_low = uaddCarry(result_low, low(uInteger1) * low(uInteger2), carry);
	result_high += carry;

	result_low = uaddCarry(result_low, (low(uInteger1) * high(uInteger2)) << 16, carry);
	result_high += carry;
	result_high += high(low(uInteger1) * high(uInteger2));

	result_low = uaddCarry(result_low, (high(uInteger1) * low(uInteger2)) << 16, carry);
	result_high += carry;
	result_high += high(high(uInteger1) * low(uInteger2));

	result_high += high(uInteger1) * high(uInteger2);

	return result_high;
}

highp uint umExtended_L(highp uint uInteger1, highp uint uInteger2)
{
	lowp uint carry = 0u;


	highp uint result_high = 0u;
	highp uint result_low = 0u;

	result_low = uaddCarry(result_low, low(uInteger1) * low(uInteger2), carry);
	result_high += carry;

	result_low = uaddCarry(result_low, (low(uInteger1) * high(uInteger2)) << 16, carry);
	result_high += carry;
	result_high += high(low(uInteger1) * high(uInteger2));

	result_low = uaddCarry(result_low, (high(uInteger1) * low(uInteger2)) << 16, carry);
	result_high += carry;
	result_high += high(high(uInteger1) * low(uInteger2));

	result_high += high(uInteger1) * high(uInteger2);

	return result_low;
}



void main()
{
	
	highp uint uInteger3 = 0x00000001u;
	highp uint uInteger1 = 0x00000002u;
	highp uint uInteger4 = 0xFFFFFFFEu;
											//	highp uint uInteger2 = 0xF0000000u;
	highp uint uInteger2 = 0x80000001u;

	bool results[32] = bool[32](
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false
				);
	highp uint result_high = 0u;
	highp uint result_low = 0u;

	highp uint msb = 0u;
	highp uint lsb = 0u;

	result_high = umExtended_H(uInteger1, uInteger2);
	result_low = umExtended_L(uInteger1, uInteger2);
	umulExtended(uInteger1, uInteger2, msb, lsb);
	results[0] = ((msb == result_high) && (lsb == result_low));

	result_high = umExtended_H(uInteger2, uInteger4);
	result_low = umExtended_L(uInteger2, uInteger4);
	umulExtended(uInteger2, uInteger4, msb, lsb);
	results[1] = ((msb == result_high) && (lsb == result_low));

	highp uvec2 msb_2;
	highp uvec2 lsb_2;

	result_high = umExtended_H(uInteger1, uInteger2);
	result_low = umExtended_L(uInteger1, uInteger2);
	umulExtended(uvec2(1u, uInteger1), uvec2(1u, uInteger2), msb_2, lsb_2);
	results[2] = ((msb_2.y == result_high) && (lsb_2.y == result_low));

	result_high = umExtended_H(uInteger2, uInteger4);
	result_low = umExtended_L(uInteger2, uInteger4);
	umulExtended(uvec2(1u, uInteger2), uvec2(1u, uInteger4), msb_2, lsb_2);
	results[3] = ((msb_2.y == result_high) && (lsb_2.y == result_low));

	highp uvec3 msb_3;
	highp uvec3 lsb_3;

	result_high = umExtended_H(uInteger1, uInteger2);
	result_low = umExtended_L(uInteger1, uInteger2);
	umulExtended(uvec3(1u, 1u, uInteger1), uvec3(1u, 1u, uInteger2), msb_3, lsb_3);
	results[4] = ((msb_3.z == result_high) && (lsb_3.z == result_low));

	result_high = umExtended_H(uInteger2, uInteger4);
	result_low = umExtended_L(uInteger2, uInteger4);
	umulExtended(uvec3(1u, 1u, uInteger2), uvec3(1u, 1u, uInteger4), msb_3, lsb_3);
	results[5] = ((msb_3.z == result_high) && (lsb_3.z == result_low));


	highp uvec4 msb_4;
	highp uvec4 lsb_4;

	result_high = umExtended_H(uInteger1, uInteger2);
	result_low = umExtended_L(uInteger1, uInteger2);
	umulExtended(uvec4(1u, 1u, 1u, uInteger1), uvec4(1u, 1u, 1u, uInteger2), msb_4, lsb_4);
	results[6] = ((msb_4.w == result_high) && (lsb_4.w == result_low));

	result_high = umExtended_H(uInteger2, uInteger4);
	result_low = umExtended_L(uInteger2, uInteger4);
	umulExtended(uvec4(1u, 1u, 1u, uInteger2), uvec4(1u, 1u, 1u, uInteger4), msb_4, lsb_4);
	results[7] = ((msb_4.w == result_high) && (lsb_4.w == result_low));
	

	gl_Position = vec4(vPosition.x / 16.0, float(results[gl_VertexID]) / 2.0, vPosition.z, 1.0);


	if(gl_VertexID < 8)
		vfColor = vColor;
	else
		vfColor = vec4(0.0, 1.0, 0.0, 1.0);
	gl_PointSize = 8.0;
}

// 0x10000u = 2^16
// in packUnorm2x16(vec2(vPosition.x, 0.5)), vPosition.x is the lower part, 0.5 is the higher part
