#version 430 core

precision mediump int;
precision mediump float;
precision mediump sampler1D;
precision mediump sampler2D;
precision mediump sampler3D;
precision mediump samplerCube;
precision mediump sampler2DArray;
precision mediump samplerBuffer;


layout(location = 0) in vec4 av4position;
//layout(location = 1) in vec3 av3colour;

layout(location = 0) uniform mat4 mvp;

out vec3 vv3colour;

void main()
{
	vv3colour = normalize(av4position.xyz);	//��һ����ɫ
    gl_Position = mvp * av4position;
}
