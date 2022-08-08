#version 430 core

out vec4 fColor;

uniform int f1; 
uniform ivec2 f2; 
uniform ivec3 f3; 
uniform ivec4 f4; 

uniform int fv1;
uniform ivec2 fv2;
uniform ivec3 fv3;
uniform ivec4 fv4;

void main()
{
	fColor = f4 + vec4(f3, 0.0) + vec4(f2, 0.0, 0.0) + vec4(f1, 0.0, 0.0, 0.0) + fv4 + vec4(fv3, 0.0) + vec4(fv2, 0.0, 0.0) + vec4(fv1, 0.0, 0.0, 0.0);
}
