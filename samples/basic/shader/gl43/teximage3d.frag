#version 430 core
precision mediump float;
precision mediump sampler3D;

out vec4 outputColor;
in vec3 texCoords;
uniform sampler3D texSampler;

void main() {
  outputColor = texture(texSampler, texCoords);
}
