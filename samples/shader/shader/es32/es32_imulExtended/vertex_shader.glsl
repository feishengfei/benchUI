#version   ///GLSL Version 3.20

//uniform float theta;
//uniform int choice;
in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;


highp int Msb(uint msb, uint lsb)
{
	highp int msb_return;
	highp int lsb_return;
	lowp uint carry;

	lsb_return = int(uaddCarry(~lsb, 1u, carry));
	msb_return = int((~msb) + carry);

	return msb_return;
}

highp int Lsb(uint msb, uint lsb)
{
	highp int msb_return;
	highp int lsb_return;
	lowp uint carry;

	lsb_return = int(uaddCarry(~lsb, 1u, carry));
	msb_return = int((~msb) + carry);

	return lsb_return;
}


void main()
{
	highp int Integer3 = 0x00000001;
	highp int Integer1 = -0x00000002;
	highp int Integer4 = 0xFFFFFFFE;
												//	highp uint uInteger2 = 0xF0000000u;
	highp int Integer2 = 0x80000001;

	bool results[32] = bool[32](
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false
				);

	int Sign;

	highp uint result_high = 0u;
	highp uint result_low = 0u;

	highp uint msb = 0u;
	highp uint lsb = 0u;

	highp int msB_1;
	highp int lsB_1;
	umulExtended(uint(abs(Integer1)), uint(abs(Integer4)), msb, lsb);
	Sign = sign(Integer1) * sign(Integer4);
	if(Sign == -1)
	{
		msB_1 = Msb(msb, lsb);
		lsB_1 = Lsb(msb, lsb);
	}
	else
	{
		msB_1 = int(msb);
		lsB_1 = int(lsb);		
	}

	highp int msB_2;
	highp int lsB_2;
	umulExtended(uint(abs(Integer2)), uint(abs(Integer4)), msb, lsb);
	Sign = sign(Integer2) * sign(Integer4);
	if(Sign == -1)
	{
		msB_2 = Msb(msb, lsb);
		lsB_2 = Lsb(msb, lsb);
	}
	else
	{
		msB_2 = int(msb);
		lsB_2 = int(lsb);		
	}

	highp int MSB = 0;
	highp int LSB = 0;
	imulExtended(Integer1, Integer4, MSB, LSB);
	results[0] = ((msB_1 == MSB) && (lsB_1 == LSB));
	imulExtended(Integer2, Integer4, MSB, LSB);
	results[1] = ((msB_2 == MSB) && (lsB_2 == LSB));

	highp ivec2 MSB_2;
	highp ivec2 LSB_2;
	imulExtended(ivec2(1, Integer1), ivec2(1, Integer4), MSB_2, LSB_2);
	results[2] = ((msB_1 == MSB_2.y) && (lsB_1 == LSB_2.y));
	imulExtended(ivec2(1, Integer2), ivec2(1, Integer4), MSB_2, LSB_2);
	results[3] = ((msB_2 == MSB_2.y) && (lsB_2 == LSB_2.y));

	highp ivec3 MSB_3;
	highp ivec3 LSB_3;
	imulExtended(ivec3(1, 1, Integer1), ivec3(1, 1, Integer4), MSB_3, LSB_3);
	results[4] = ((msB_1 == MSB_3.z) && (lsB_1 == LSB_3.z));
	imulExtended(ivec3(1, 1, Integer2), ivec3(1, 1, Integer4), MSB_3, LSB_3);
	results[5] = ((msB_2 == MSB_3.z) && (lsB_2 == LSB_3.z));

	highp ivec4 MSB_4;
	highp ivec4 LSB_4;
	imulExtended(ivec4(1, 1, 1, Integer1), ivec4(1, 1, 1, Integer4), MSB_4, LSB_4);
	results[6] = ((msB_1 == MSB_4.w) && (lsB_1 == LSB_4.w));
	imulExtended(ivec4(1, 1, 1, Integer2), ivec4(1, 1, 1, Integer4), MSB_4, LSB_4);
	results[7] = ((msB_2 == MSB_4.w) && (lsB_2 == LSB_4.w));


	gl_Position = vec4(vPosition.x / 16.0, float(results[gl_VertexID]) / 2.0, vPosition.z, 1.0);


	if(gl_VertexID < 8)
		vfColor = vColor;
	else
		vfColor = vec4(0.0, 1.0, 0.0, 1.0);

	gl_PointSize = 8.0;
}

// 0x10000u = 2^16
// in packUnorm2x16(vec2(vPosition.x, 0.5)), vPosition.x is the lower part, 0.5 is the higher part
