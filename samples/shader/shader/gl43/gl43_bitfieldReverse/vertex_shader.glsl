#version   ///GLSL Version 3.20

//uniform float theta;
//uniform int choice;
in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

uint bfieldReverse(uint value)
{	
	uint R_value = 0u;
	const int bits = 32;
	for(int i = 0; i < bits; i++){
		R_value += ((value >> i) & 0x1u) << ((bits - 1) - i);
	}
	return R_value;
}

int bfieldReverse(int value)
{	
	int R_value = 0;
	const int bits = 32;
	for(int i = 0; i < bits; i++){
		R_value += ((value >> i) & 0x1) << ((bits - 1) - i);
	}
	return R_value;
}


void main()
{
	uint uValue = 0x33553535u;

	bool a[32] = bool[32](
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false
				);

	for(int i = 0; i < 16; i++){
		a[i] = (
				(bfieldReverse(uValue) == bitfieldReverse(uValue)) &&
				(bfieldReverse(uValue) == ((bitfieldReverse(uvec2(1u, uValue))).y))  &&
				(bfieldReverse(uValue) == ((bitfieldReverse(uvec3(1u, 1u, uValue))).z))  &&
				(bfieldReverse(uValue) == ((bitfieldReverse(uvec4(1u, 1u, 1u, uValue))).w))
			   );				
	}

	int Value = 0x33553535;



	for(int i = 0; i < 16; i++){
		a[i + 16] = (
				(bfieldReverse(Value) == bitfieldReverse(Value)) &&
				(bfieldReverse(Value) == ((bitfieldReverse(ivec2(1, Value))).y))  &&
				(bfieldReverse(Value) == ((bitfieldReverse(ivec3(1, 1, Value))).z))  &&
				(bfieldReverse(Value) == ((bitfieldReverse(ivec4(1, 1, 1, Value))).w))
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
