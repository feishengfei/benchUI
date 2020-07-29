#version 430 core

out vec4 fColor;

layout(location=0) uniform dvec3 uColor;

void main()
{
	fColor = vec4(uColor, 1.0);
}
