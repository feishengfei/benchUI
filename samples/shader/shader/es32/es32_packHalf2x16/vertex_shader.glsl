#version   ///GLSL Version 3.20

//uniform float theta;
//uniform int choice;
in vec4 vPosition;
in vec4 vColor;
out vec4 vfColor;

#define F16_EXPONENT_BITS 0x1F
#define F16_EXPONENT_SHIFT 10
#define F16_EXPONENT_BIAS 15
#define F16_MANTISSA_BITS 0x3ff
#define F16_MANTISSA_SHIFT (23 - F16_EXPONENT_SHIFT)
#define F16_MAX_EXPONENT (F16_EXPONENT_BITS << F16_EXPONENT_SHIFT)

uint F32toF16(float val)
{
	// decode val
	uint f32 = floatBitsToUint(val);
	uint f16 = 0u;
	int sign = int((f32 >> 16) & 0x8000u);
	int exponent = int((f32 >> 23) & 0xffu) - 127; 
	int mantissa = int(f32 & 0x007fffffu);

	// encode f32 to f16
	if (exponent == 128){
		f16 = uint(sign | F16_MAX_EXPONENT);
		if (mantissa != 0)
			f16 |= uint(mantissa & F16_MANTISSA_BITS);
	}
	else if (exponent > 15){
		f16 = uint(sign | F16_MAX_EXPONENT);
	}
	else if (exponent > -15){
		exponent += F16_EXPONENT_BIAS;
		mantissa >>= F16_MANTISSA_SHIFT;
		f16 = uint(sign | exponent << F16_EXPONENT_SHIFT | mantissa);
	}
	else{
		f16 = uint(sign);
	}

	return f16;
}



void main()
{
	highp uint y1 = packHalf2x16(vec2(vPosition.x, 0.5));
	highp uint y2 = F32toF16(vPosition.x) + (F32toF16(0.5) << 16);

	gl_Position = vec4(vPosition.x / 1.0, float(y1 - y2) / 2.0, vPosition.z, 1.0);



	vfColor = vColor;
	gl_PointSize = 6.0;
}

// 0x10000u = 2^16
// in packUnorm2x16(vec2(vPosition.x, 0.5)), vPosition.x is the lower part, 0.5 is the higher part
