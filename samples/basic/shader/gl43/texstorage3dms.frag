#version 430 core

//#extension GL_EXT_gpu_shader4 : enable
//#extension GL_ARB_texture_multisample : enable

in vec3 vTexColor;
out vec4 FragColor;
layout(location = 2) uniform isampler2DMSArray diffuse;
layout(location = 3) uniform int nMultiSample;

void main(){
    ivec3 texSize = textureSize(diffuse);
    vec4 ftexcolor = vec4(0.0);
    for(int i = 0; i < nMultiSample; i++){
    ftexcolor += texelFetch(diffuse, ivec3(vTexColor*texSize), i);
    }
    FragColor = ftexcolor/nMultiSample;
}