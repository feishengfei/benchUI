#version 320 es  
precision mediump float;


layout (binding = 1 ,offset = 0) uniform atomic_uint at;

uniform Uniforms{
	float a;
	float b;

};
out vec4 FragColor; 

void main()
{
	/*uint a = atomicCounterIncrement(at);
	uint b = atomicCounterIncrement(at);
	if(a == b)
	
        	FragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );
	
	else*/
		FragColor = vec4 ( 0.0, 0.0, 1.0, 1.0 );
}
