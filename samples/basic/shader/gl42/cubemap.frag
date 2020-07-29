#version 430 core
precision mediump float;
precision mediump samplerCube;

out vec4 outputColor;
in vec3 vnormal;
uniform samplerCube texSampler;

void main() {
  outputColor = texture(texSampler, vnormal);
}
