#version 320 es                                  

precision mediump float;

precision highp float;
precision highp int;
precision highp sampler2DArray;
layout(std140, column_major) uniform;

uniform sampler2DArray texSampler;

//in vec2 v2Texcoord;
in vec3 v2Texcoord;

out vec4 Color;

void main()
{
//	Color = texture(texSampler, vec3(v2Texcoord, 0.0));
	Color = texture(texSampler, v2Texcoord);
}
