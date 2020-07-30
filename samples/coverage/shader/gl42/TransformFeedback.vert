#version 430 core

precision highp float;
in float pos;

void main()
{
     gl_Position = vec4(pos, 0.2*gl_InstanceID, 0.0, 1.0);
}
