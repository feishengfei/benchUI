#version 430 core
precision highp float;

subroutine vec4 SetPosType(vec2 pos);
subroutine uniform SetPosType SetPos;

subroutine(SetPosType)
vec4 Normal(vec2 a)
{
	return vec4(a, 0.0, 1.0);
}

subroutine(SetPosType)
vec4 MirrorX(vec2 a)
{
	return vec4(-a.x, a.y, 0.0, 1.0);
}

subroutine(SetPosType)
vec4 MirrorY(vec2 a)
{
	return vec4(a.x, -a.y, 0.0, 1.0);
}

in vec2 a_v2Position;

void main()
{
    gl_Position = SetPos(a_v2Position);
}
