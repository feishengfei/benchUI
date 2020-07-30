#version 100

precision highp float;
precision highp int;

uniform sampler2D Diffuse;

varying vec2 v_v2TexCoord;

void main()
{
	gl_FragColor = texture2D(Diffuse, v_v2TexCoord, 0);
}
