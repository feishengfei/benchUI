#version 300 es    
precision mediump float;
precision mediump sampler3D;

out vec4 outputColor;
in vec3 texCoords;
uniform sampler3D texSampler;

void main() {
  outputColor = texture(texSampler, texCoords);
//outputColor = vec4(1.0,0.0,0.0,0.0);
}
