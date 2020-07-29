#version 430 core

layout(binding = 0, offset = 0) uniform atomic_uint aRed;
layout(binding = 0, offset = 4) uniform atomic_uint aGreen;
layout(binding = 0, offset = 8) uniform atomic_uint aBlue;

uniform float fPixel = 1.0/(480*320);

out vec4 FragColor;

void main(){
    float r = atomicCounterIncrement(aRed)*fPixel;
    float g = atomicCounterIncrement(aGreen)*fPixel;
    float b = atomicCounterIncrement(aBlue)*fPixel;

    FragColor = vec4(r, g, b, 1.0);
}