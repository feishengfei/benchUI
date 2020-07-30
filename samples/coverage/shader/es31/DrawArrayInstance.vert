#version 310 es  
precision mediump float;

uniform Uniforms{
	float a;
	float b;

};

uniform float resourcet_1;
uniform float resourcet_2;

in float inValue;
out float outValue;
in vec2 a_v4Position;


void main()
{
    gl_Position = vec4(a_v4Position, resourcet_1,resourcet_2);
    outValue = sqrt(inValue);
	
}
