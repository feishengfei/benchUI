#version 430 core

layout(location = 0) in vec2 aPos;
layout(location = 0) uniform mat2x2 pos;
layout(location = 1) uniform mat3x3 pos1;
layout(location = 4) uniform mat4x4 pos2;
layout(location = 8) uniform mat2x3 pos3;
layout(location = 10) uniform mat3x2 pos4;
layout(location = 12) uniform mat2x4 pos5;
layout(location = 14) uniform mat4x2 pos6;
layout(location = 16) uniform mat3x4 pos7;
layout(location = 19) uniform mat4x3 pos8;
void main()
{
    float a=pos[0][0]+pos[1][1];
    float b=pos1[0][0]+pos1[1][1]+pos1[2][2];
    float c=pos2[0][0]+pos2[1][1]+pos2[2][2]+pos2[3][3];
    float d=pos3[0][0]+pos3[1][2];
    float e=pos4[0][0]+pos4[2][1];
    float f=pos5[0][0]+pos5[1][3];
    float g=pos6[0][0]+pos6[3][1];
    float h=pos7[0][0]+pos7[2][3];
    float i=pos8[0][0]+pos8[3][2];
    float j=a+b+c+d;
    float k=e+f+g+h+i;
    gl_Position = vec4(aPos.x + j, aPos.y + k, 0.0, 1.0);
}
