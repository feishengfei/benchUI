#version 430 core

layout(location = 0) in vec2 vPos;
layout(location = 1) in vec3 vColor;

layout(binding = 0, offset = 0) uniform atomic_uint aX;
layout(binding = 0, offset = 4) uniform atomic_uint aY;
layout(binding = 0, offset = 8) uniform atomic_uint aRed;
layout(binding = 0, offset = 12) uniform atomic_uint aGreen;
layout(binding = 0, offset = 16) uniform atomic_uint aBlue;

uniform float Index = 0.1;

out vec3 fColor;

void main()
{
    float posx = vPos.x - atomicCounterIncrement(aX)*Index;
    float posy = vPos.y + atomicCounterIncrement(aY)*Index;
	gl_Position = vec4(posx, posy, 0.0, 1.0);

	float r = vColor.r + atomicCounterIncrement(aRed)*Index;
    float g = vColor.g + atomicCounterIncrement(aGreen)*Index;
    float b = vColor.b + atomicCounterIncrement(aBlue)*Index;
	fColor = vec3(r, g, b);
}


