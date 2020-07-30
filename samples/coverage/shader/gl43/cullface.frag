#version 430 core

layout(early_fragment_tests) in;
layout(location = 1) uniform sampler2D texture1;

in vec2 TexCoord;
out vec4 FragColor;

void main()
{
	FragColor = texture(texture1, TexCoord);
}
