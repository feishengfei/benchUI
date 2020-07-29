#version   ///GLSL Version 3.20

//uniform float theta;
//uniform int choice;
in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

lowp int fLSB(uint value)
{	
	const int bits = 32;
	for(int i = 0; i < bits; i++){
		if(1u == ((value >> i) & 0x1u))
			return i;
	}
	return -1;
}

lowp int fLSB(int value)
{	
	const int bits = 32;
	for(int i = 0; i < bits; i++){
		if(1 == ((value >> i) & 0x1))
			return i;
	}
	return -1;
}


void main()
{
	uint uValue = 0x01000101u;

	bool a[32] = bool[32](
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false
				);

	for(int i = 0; i < 16; i++){
		uValue <<= i;
		a[i] = (
				(fLSB(uValue) == findLSB(uValue)) &&
				(fLSB(uValue) == ((findLSB(uvec2(1u, uValue))).y))  &&
				(fLSB(uValue) == ((findLSB(uvec3(1u, 1u, uValue))).z))  &&
				(fLSB(uValue) == ((findLSB(uvec4(1u, 1u, 1u, uValue))).w))
			   );				
	}

	int Value = 0x01000101;

	for(int i = 0; i < 16; i++){
		Value <<= i;
		a[i + 16] = (
				(fLSB(Value) == findLSB(Value)) &&
				(fLSB(Value) == ((findLSB(ivec2(1, Value))).y))  &&
				(fLSB(Value) == ((findLSB(ivec3(1, 1, Value))).z))  &&
				(fLSB(Value) == ((findLSB(ivec4(1, 1, 1, Value))).w))
			   );				
	}


	gl_Position = vec4(vPosition.x / 16.0, float(a[gl_VertexID]) / 2.0, vPosition.z, 1.0);
//	gl_Position = vec4(vPosition.x / 16.0, float(((~x) >> gl_VertexID) & 0x1) / 2.0, vPosition.z, 1.0);


	if(gl_VertexID < 16)
		vfColor = vColor;
	else 
		vfColor = vColor * 0.5;	
		
	gl_PointSize = 8.0;
}

// 0x10000u = 2^16
// in packUnorm2x16(vec2(vPosition.x, 0.5)), vPosition.x is the lower part, 0.5 is the higher part
