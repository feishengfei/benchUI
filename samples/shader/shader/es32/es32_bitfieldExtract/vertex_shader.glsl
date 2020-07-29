#version   ///GLSL Version 3.20

//uniform float theta;
//uniform int choice;
in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

uint bExtract(uint value, int offset, int bits)
{	
	if(0 == bits)
		return 0u;
	else
		return (value >> offset) & ((0x1u << bits) - 1u); 
}

int bExtract(int value, int offset, int bits)
{
	if(0 == bits)
		return 0;
	else
		return ((value << (32 - (offset + bits))) >> (32 - bits));
}


void main()
{
	uint uInteger = 0x33553535u;
	bool a[32] = bool[32](
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false
				);

	for(int i = 0; i < 16; i++){
		a[i] = (
				(bExtract(uInteger, 8, i) == bitfieldExtract(uInteger, 8, i)) &&
				(bExtract(uInteger, 8, i) == ((bitfieldExtract(uvec2(1u, uInteger), 8, i)).y))  &&
				(bExtract(uInteger, 8, i) == ((bitfieldExtract(uvec3(1u, 1u, uInteger), 8, i)).z))  &&
				(bExtract(uInteger, 8, i) == ((bitfieldExtract(uvec4(1u, 1u, 1u, uInteger), 8, i)).w))
			   );				
	}

	int Integer = 0x33553535;

	for(int i = 0; i < 16; i++){
		a[i + 16] = (
				(bExtract(Integer, 8, i) == bitfieldExtract(Integer, 8, i)) &&
				(bExtract(Integer, 8, i) == ((bitfieldExtract(ivec2(1, Integer), 8, i)).y))  &&
				(bExtract(Integer, 8, i) == ((bitfieldExtract(ivec3(1, 1, Integer), 8, i)).z))  &&
				(bExtract(Integer, 8, i) == ((bitfieldExtract(ivec4(1, 1, 1, Integer), 8, i)).w))
			   );
	}




	gl_Position = vec4(vPosition.x / 16.0, float(a[gl_VertexID]) / 2.0, vPosition.z, 1.0);

	if(gl_VertexID < 16)
		vfColor = vColor;
	else 
		vfColor = vColor * 0.5;	

	gl_PointSize = 8.0;
}

// 0x10000u = 2^16
// in packUnorm2x16(vec2(vPosition.x, 0.5)), vPosition.x is the lower part, 0.5 is the higher part
