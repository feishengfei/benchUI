#version 430 core

out vec4 Color; 

subroutine vec4 SetColorType();
subroutine uniform SetColorType SetColor;

subroutine(SetColorType)
vec4 Red()
{
	return vec4(1.0, 0.0, 0.0, 0.0);
}

subroutine(SetColorType)
vec4 Green()
{
	return vec4(0.0, 1.0, 0.0, 0.0);
}

void main()
{
    Color = SetColor();
}
