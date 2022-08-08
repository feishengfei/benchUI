#version 310 es    
precision mediump float;

out vec4 outputColor;
in vec2 texCoords;
uniform sampler2D texSampler;

void main() {
  outputColor = texture(texSampler, texCoords);
}
