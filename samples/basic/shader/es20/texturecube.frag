/*
 * fragment shader: uniformui
 */
#version 300 es    
precision mediump float;
precision mediump samplerCube;

out vec4 outputColor;
in vec3 vnormal;
uniform samplerCube texSampler;

void main() {
  outputColor = texture(texSampler, vnormal);
//outputColor = vec4(1.0,0.0,0.0,0.0);
}
