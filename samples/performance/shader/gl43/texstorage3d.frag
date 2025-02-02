#version 430 core
   
precision highp float;
precision highp int;
precision mediump sampler2DArray;

out vec4 Color;
in vec2 OutTexcoord;
uniform sampler2DArray Diffuse;

void main() {

	Color = texture(Diffuse, vec3(OutTexcoord, 1.0));
}
