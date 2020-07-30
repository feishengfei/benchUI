#version 430 core

out vec4 fColor;

uniform float f1; 
uniform vec2 f2; 
uniform vec3 f3; 
uniform vec4 f4; 

uniform float fv1;
uniform vec2 fv2;
uniform vec3 fv3;
uniform vec4 fv4;

void main()
{
	fColor = f4 + vec4(f3, 0.0) + vec4(f2, 0.0, 0.0) + vec4(f1, 0.0, 0.0, 0.0) + fv4 + vec4(fv3, 0.0) + vec4(fv2, 0.0, 0.0) + vec4(fv1, 0.0, 0.0, 0.0);
}
