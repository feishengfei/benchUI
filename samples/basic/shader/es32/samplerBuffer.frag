#version 320 es    
precision mediump float;
precision mediump samplerBuffer;

out vec4 outputColor;
uniform samplerBuffer s;

void main() {
  outputColor = texelFetch(s, 0);
//outputColor = vec4(1.0,0.0,0.0,0.0);
}
