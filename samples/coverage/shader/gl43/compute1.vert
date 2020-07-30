#version 430 core

#pragma debug(on)

precision mediump float;

in vec3 a_v4Position;


void main()
{
	gl_Position =vec4(a_v4Position,1.0);
}
