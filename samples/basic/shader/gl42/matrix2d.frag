#version 430 core

out vec4 fColor;

layout(location=0) uniform dmat2x2 uColor;

void main()
{
	fColor = vec4(ucolor[0], 0.0, 1.0);
}
