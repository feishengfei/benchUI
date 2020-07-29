#version 320 es  

precision highp float;
precision highp int;

in vec2 Position;
in vec2 Texcoord;

out vec2 OutTexcoord;
//out float OutInstance;

void main()
{
//	vec2 Offset = vec2(gl_InstanceID % 5, gl_InstanceID / 5) - vec2(2, 1);
//	OutInstance = gl_InstanceID;
	OutTexcoord = Texcoord;
//	gl_Position = vec4(Position + Offset, 0.0, 1.0);
	gl_Position = vec4(Position, 0.0, 1.0);
}
