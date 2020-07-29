#version  //GLSL Version 3.20; OpenGL es 3.2

precision highp float;

layout (binding = 0, offset = 0) uniform atomic_uint atomicNum;
layout (binding = 0, offset = 4) uniform atomic_uint atomicDecrease;
layout (binding = 0, offset = 8) uniform atomic_uint atomicIncrease;

in vec4 vfColor;
sample in vec4 vfFunc;

out vec4 FragColor;

float is_inner(vec2 point)
{
	if( point.x < 200.0)
		return -1.0;
	if( point.y < 200.0)
		return -1.0;
	if( point.x  + point.y  > 600.0)
		return -1.0;
	return 0.0;
}

void main()
{		

	if(gl_HelperInvocation == false)
		FragColor = vfColor + dFdy(vfFunc) * 0.0000001;

}
