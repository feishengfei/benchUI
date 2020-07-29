#version 430 core
precision mediump float;
precision mediump sampler1D;

out vec4 outputColor;
uniform sampler1D texSampler;

void main() {
  outputColor = texture(texSampler, 1.0);
}
