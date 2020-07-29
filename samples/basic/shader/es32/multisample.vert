#version 320 es                                  

#define POSITION	0
#define TEXCOORD	4

precision highp float;
precision highp int;
layout(std140, column_major) uniform;

layout(location = POSITION) in vec3 Position;
//layout(location = TEXCOORD) in vec2 Texcoord;
layout(location = TEXCOORD) in vec3 Texcoord;

out vec3 v2Texcoord;
//out vec2 v2Texcoord;

void main()
{
	v2Texcoord = Texcoord;
	gl_Position = vec4(Position, 1.0);
}
