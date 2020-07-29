#version 430 core

out vec4 fColor;

uniform uint f1;
uniform uvec2 f2; 
uniform uvec3 f3; 
uniform uvec4 f4; 

uniform uint fv1;
uniform uvec2 fv2;
uniform uvec3 fv3;
uniform uvec4 fv4;

void main()
{
	fColor = f4 + vec4(f3, 0.0) + vec4(f2, 0.0, 0.0) + vec4(f1, 0.0, 0.0, 0.0) + fv4 + vec4(fv3, 0.0) + vec4(fv2, 0.0, 0.0) + vec4(fv1, 0.0, 0.0, 0.0);
}
