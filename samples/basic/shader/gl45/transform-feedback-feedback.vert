#version 430 core

precision mediump int;
precision mediump float;
precision mediump sampler1D;
precision mediump sampler2D;
precision mediump sampler3D;
precision mediump samplerCube;
precision mediump sampler2DArray;
precision mediump samplerBuffer;


#define POSITION	0
#define COLOR		3
#define FRAG_COLOR	0

layout(std140, column_major) uniform;

layout(location = 0) in vec4 Position;
layout(location = 3) in vec4 Color;

out block
{
	vec4 Color;
} Out;

out gl_PerVertex
{
	vec4 gl_Position;
};

void main()
{
	gl_Position = Position;
	Out.Color = Color;
}

