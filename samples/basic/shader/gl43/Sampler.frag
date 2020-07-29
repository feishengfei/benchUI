#version 430 core
precision mediump float;

out vec4 outputColor;
smooth in vec2 texCoords;
layout(location = 0) uniform sampler2D texSampler;

void main() {
  outputColor = texture(texSampler, texCoords);
}
