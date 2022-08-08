#version 430 core

out vec4 fColor;

layout(location=0) uniform dvec4 uColor;

void main()
{
	fColor = vec4(uColor);
}
