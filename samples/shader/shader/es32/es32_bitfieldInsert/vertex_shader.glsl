#version   ///GLSL Version 3.20

//uniform float theta;
//uniform int choice;
in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

uint bfieldInsert(uint base, uint insert, int offset, int bits)
{	
	uint mask_base;
	mask_base = ((0x1u << (offset + bits)) - 1u) - ((0x1u << offset) - 1u);
	mask_base = (~ mask_base);
	base = base & mask_base;   /// if bits = 0, we have mask_base = 0xFFFFFFFFu

	uint mask_insert;
	mask_insert = ((0x1u << bits) - 1u);
	insert = ((insert & mask_insert) << offset);  /// if bits = 0, we have mask_insert = 0x00000000u

	return base + insert; 
}

int bfieldInsert(int base, int insert, int offset, int bits)
{
	uint mask_base;
	mask_base = ((0x1u << (offset + bits)) - 1u) - ((0x1u << offset) - 1u);
	mask_base = (~ mask_base);
	base = base & int(mask_base);

	uint mask_insert;
	mask_insert = ((0x1u << bits) - 1u);
	insert = ((insert & int(mask_insert)) << offset);
	return base + insert; 
}


void main()
{
	uint uInteger = 0x33553535u;
	uint uInsert = 0x6F985245u;

	bool a[32] = bool[32](
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false
				);

	for(int i = 0; i < 16; i++){
		a[i] = (
				(bfieldInsert(uInteger, uInsert, 8, i) == bitfieldInsert(uInteger, uInsert, 8, i)) &&
				(bfieldInsert(uInteger, uInsert, 8, i) == ((bitfieldInsert(uvec2(1u, uInteger), uvec2(1u, uInsert), 8, i)).y))  &&
				(bfieldInsert(uInteger, uInsert, 8, i) == ((bitfieldInsert(uvec3(1u, 1u, uInteger), uvec3(1u, 1u, uInsert), 8, i)).z))  &&
				(bfieldInsert(uInteger, uInsert, 8, i) == ((bitfieldInsert(uvec4(1u, 1u, 1u, uInteger), uvec4(1u, 1u, 1u, uInsert), 8, i)).w))
			   );				
	}




	int Integer = 0x33553535;
	int Insert = 0x6F985245;


	for(int i = 0; i < 16; i++){
		a[i + 16] = (
				(bfieldInsert(Integer, Insert, 8, i) == bitfieldInsert(Integer, Insert, 8, i)) &&
				(bfieldInsert(Integer, Insert, 8, i) == ((bitfieldInsert(ivec2(1, Integer), ivec2(1, Insert), 8, i)).y))  &&
				(bfieldInsert(Integer, Insert, 8, i) == ((bitfieldInsert(ivec3(1, 1, Integer), ivec3(1, 1, Insert), 8, i)).z))  &&
				(bfieldInsert(Integer, Insert, 8, i) == ((bitfieldInsert(ivec4(1, 1, 1, Integer), ivec4(1, 1, 1, Insert), 8, i)).w))
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
