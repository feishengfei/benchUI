#version 430 core
#extension GL_EXT_gpu_shader4 : enable
#extension GL_ARB_texture_multisample : enable
precision lowp sampler2DMSArray;
in vec2 texCoord;
layout(location = 0) uniform int layer;
uniform sampler2DMSArray sampler0;

out vec4 FragColor;

void main()                                
{                                          
    FragColor = texelFetch(sampler0, ivec3(ivec2(texCoord*16+vec2(0.5)), layer), 0);
}                                          