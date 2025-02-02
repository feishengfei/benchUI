#version  430 core ///GLSL Version 3.20

layout (triangles, equal_spacing, ccw, point_mode) in;

in vec4 vtcColor[];
out vec4 tefColor;


void main()
{

	float u = gl_TessCoord.x;
	float v = gl_TessCoord.y;
	float w = gl_TessCoord.z;

	gl_Position = u * gl_in[0].gl_Position + v * gl_in[1].gl_Position + w * gl_in[2].gl_Position;

	tefColor = vtcColor[0];

}

