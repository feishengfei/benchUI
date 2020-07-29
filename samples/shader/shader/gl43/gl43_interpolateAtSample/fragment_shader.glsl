#version             //GLSL Version 3.20; OpenGL es 3.2

precision highp float;

in vec4 vfColor;

sample in vec4 vfFunc;
sample in vec3 vfFunc_3;
sample in vec2 vfFunc_2;
sample in float vfFunc_1;

layout(location = 0) uniform int NumSamples;

out vec4 FragColor;

void main()
{		
	if( 
			( vfFunc == interpolateAtSample(vfFunc, gl_SampleID) )
		&&	( vfFunc_1 == interpolateAtSample(vfFunc_1, gl_SampleID) )	
		&&	( vfFunc_2 == interpolateAtSample(vfFunc_2, gl_SampleID) )	
		&&	( vfFunc_3 == interpolateAtSample(vfFunc_3, gl_SampleID) )

		
		&& ( vfFunc == interpolateAtOffset(vfFunc, gl_SamplePosition - vec2(0.50, 0.50)) )
		&& ( vfFunc_1 == interpolateAtOffset(vfFunc_1, gl_SamplePosition - vec2(0.50, 0.50)) )
		&& ( vfFunc_2 == interpolateAtOffset(vfFunc_2, gl_SamplePosition - vec2(0.50, 0.50)) )
		&& ( vfFunc_3 == interpolateAtOffset(vfFunc_3, gl_SamplePosition - vec2(0.50, 0.50)) )		


//		&& abs((interpolateAtOffset(vfFunc, vec2(0.4, 0.0))).x - (interpolateAtOffset(vfFunc, vec2(0.2, 0.0))).x - 0.2) < 0.0001
//		&& interpolateAtOffset(vfFunc, vec2(0.5, 0.0)) == interpolateAtOffset(vfFunc, vec2(0.46, 0.0))
		&& (gl_NumSamples == NumSamples)
	   )
		FragColor = vec4(0.0, 1.0, 0.0, 1.0);
	else
		FragColor = vfColor;
}
