#version 430 core

//#extension GL_EXT_gpu_shader4 : enable
//#extension GL_ARB_texture_multisample : enable

out vec4 FragColor;
layout(location = 2) uniform isampler2DMS diffuse;
centroid in vec2 vTexCoord;
layout(location = 3) uniform int nMultiSample;

void main(){
 ivec2 texSize = textureSize(diffuse);
    vec4 ftexcolor = vec4(0.0);
    for(int i = 0; i < nMultiSample; i++){
    ftexcolor += texelFetch(diffuse, ivec2(vTexCoord*texSize), i);
    }
    FragColor = ftexcolor/nMultiSample;
}
