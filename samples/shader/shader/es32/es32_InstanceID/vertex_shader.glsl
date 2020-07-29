#version   ///GLSL Version 3.20

in vec4 vPosition;
in vec4 vColor;
in vec4 vFunc;

layout(location = 0) uniform float offsets[3];

out vec4 vfColor;
out vec4 vfFunc;


void main()
{
	gl_Position = vPosition + vec4(offsets[gl_InstanceID], 0.0, 0.0, 0.0);
	vfColor = vColor;
	vfFunc = vFunc;
}

