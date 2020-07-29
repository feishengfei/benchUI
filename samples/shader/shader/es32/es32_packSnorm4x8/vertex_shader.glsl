#version   ///GLSL Version 3.20

//uniform float theta;
//uniform int choice;
in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

void main()
{
	highp uint y1 = packSnorm4x8(vec4(vPosition.x, 0.5, -0.2, 0.3));
	highp uint y2 = uint(
							(int(round(clamp(vPosition.x, -1.0, 1.0) * 127.0)) & 0xFF) +							
							((int(round(clamp(0.5, -1.0, 1.0) * 127.0)) & 0xFF) << 8) +
							((int(round(clamp(-0.2, -1.0, 1.0) * 127.0)) & 0xFF) << 16) +
							(int(round(clamp(0.3, -1.0, 1.0) * 127.0)) << 24)

						);
	gl_Position = vec4(vPosition.x / 1.0, float(y2 - y1) / 1.0, vPosition.z, 1.0);
	vfColor = vColor;
	gl_PointSize = 8.0;
}

// 0x10000u = 2^16
// in packUnorm2x16(vec2(vPosition.x, 0.5)), vPosition.x is the lower part, 0.5 is the higher part
