#version 430 core

precision mediump float;
precision mediump sampler2D;

out vec4 outputColor;
in vec2 texCoords;
uniform sampler2D texSampler;

void main() {
  outputColor = texture(texSampler, texCoords);
}
