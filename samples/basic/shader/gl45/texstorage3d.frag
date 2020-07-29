#version 430 core

precision mediump int;
precision mediump float;
precision mediump sampler1D;
precision mediump sampler2D;
precision mediump sampler3D;
precision mediump samplerCube;
precision mediump sampler2DArray;
precision mediump samplerBuffer;

   

out vec4 Color;
in vec2 OutTexcoord;
uniform sampler2DArray Diffuse;

void main() {

	Color = texture(Diffuse, vec3(OutTexcoord, 1.0));
}
