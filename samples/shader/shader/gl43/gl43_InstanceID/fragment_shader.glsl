#version  //GLSL Version 3.20; OpenGL es 3.2

precision highp float;

layout (binding = 0, offset = 0) uniform atomic_uint atomicNum;
layout (binding = 0, offset = 4) uniform atomic_uint atomicDecrease;
layout (binding = 0, offset = 8) uniform atomic_uint atomicIncrease;

in vec4 vfColor;
in vec4 vfFunc;

out vec4 FragColor;

void main()
{		
		FragColor = vfColor + vfFunc* 0.0000001;
}
