#version 430 core

precision mediump int;
precision mediump float;
precision mediump sampler1D;
precision mediump sampler2D;
precision mediump sampler3D;
precision mediump samplerCube;
precision mediump sampler2DArray;
precision mediump samplerBuffer;


layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;

out VS_OUT {
    vec3 color;
}vs_out;

void main()
{
	vs_out.color = aColor;
	gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
}
