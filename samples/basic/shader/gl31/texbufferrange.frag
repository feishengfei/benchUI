#version 430 core

precision mediump float;
precision mediump samplerBuffer;

out vec4 outputColor;
uniform samplerBuffer s;

void main() {
  outputColor = texelFetch(s, 0);
}
