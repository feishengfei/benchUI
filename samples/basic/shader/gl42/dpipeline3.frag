#version 430 core

out vec4 fColor;

layout(location=0) uniform dvec2 uColor;

void main()
{
	fColor = vec4(uColor, 0.0, 1.0);
}
