#version 320 es  
precision mediump float;

uniform Uniforms{
	float a;
	float b;

};

uniform float resourcet_1;
uniform float resourcet_2;
uniform vec2 resourcet_3;
uniform int valu_int;
uniform uint valu_ulint;


in float inValue;
out float outValue;
in vec2 a_v4Position;


void main()
{
    float a = float(valu_int);
    float b = float(valu_ulint);	
    gl_Position = vec4(a_v4Position, b*a*resourcet_1,resourcet_2);
    outValue = sqrt(inValue);
	
}
