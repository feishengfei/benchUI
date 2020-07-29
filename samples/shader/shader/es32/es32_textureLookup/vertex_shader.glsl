#version   ///GLSL Version 3.20

in vec4 vPosition;
in vec4 vColor;
in vec2 vTexCoord;

out vec4 vfColor;
out vec2 vfTexCoord;


void main()
{

	mat4 project = mat4(
					 1,  0, 0, 0,
					 0,  1, 0, 0,
					 0,  0, -1, 0,
					 0,  0, 0, 1
				);	
	gl_Position = project * vPosition;
	vfColor = vColor;
	vfTexCoord = vTexCoord;


		
//	gl_PointSize = 8.0;
}

// 0x10000u = 2^16
// in packUnorm2x16(vec2(vPosition.x, 0.5)), vPosition.x is the lower part, 0.5 is the higher part
