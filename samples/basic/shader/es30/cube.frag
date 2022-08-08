#version 300 es    
precision mediump float;

out vec4 outputColor;
in vec4 Color;

void main() {
  outputColor = Color;
}
