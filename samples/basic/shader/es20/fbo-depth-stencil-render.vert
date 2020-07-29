#version 100

precision highp float;
precision highp int;

attribute vec2 Position;
attribute vec2 Texcoord;

varying vec4 v_v4FillColor;
varying vec2 v_v2TexCoord;

uniform mat4 MVP;

void main()
{	
	v_v2TexCoord = Texcoord;
	gl_Position = Transform.MVP * vec4(Position, 0.0, 1.0);
}

