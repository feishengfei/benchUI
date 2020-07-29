#version 430 core

in float a;

out VS_OUT {
    float angle;
} vs_out;

const float Pi = 3.1415926;

void main()
{
   vs_out.angle = radians(a*360/6);
}
