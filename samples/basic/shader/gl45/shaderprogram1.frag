#version 430 core

precision mediump int;
precision mediump float;
precision mediump sampler1D;
precision mediump sampler2D;
precision mediump sampler3D;
precision mediump samplerCube;
precision mediump sampler2DArray;
precision mediump samplerBuffer;


in vec4 v_color;
out vec4 fragcolor;
void main()
{
	fragcolor =  v_color;
}
