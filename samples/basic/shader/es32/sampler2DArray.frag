#version 320 es
   
precision highp float;
precision highp int;
precision mediump sampler2DArray;

out vec4 Color;
in vec2 OutTexcoord;
//in float OutInstance;
uniform sampler2DArray Diffuse;

void main() {
//Color = texture(Diffuse, vec3(OutTexcoord, OutInstance));
	Color = texture(Diffuse, vec3(OutTexcoord, 0.0));
}
