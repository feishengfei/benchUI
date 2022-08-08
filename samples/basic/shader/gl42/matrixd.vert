#version 430 core

layout(location = 0) in dvec2 aPos;
layout(location = 0) uniform dmat2x2 pos;
layout(location = 2) uniform dmat3x3 pos1;
layout(location = 7) uniform dmat4x4 pos2;
layout(location = 15) uniform dmat2x3 pos3;
layout(location = 18) uniform dmat3x2 pos4;
layout(location = 21) uniform dmat2x4 pos5;
layout(location = 25) uniform dmat4x2 pos6;
layout(location = 29) uniform dmat3x4 pos7;
layout(location = 35) uniform dmat4x3 pos8;
void main()
{
    double a=pos[0][0]+pos[1][1];
    double b=pos1[0][0]+pos1[1][1]+pos1[2][2];
    double c=pos2[0][0]+pos2[1][1]+pos2[2][2]+pos2[3][3];
    double d=pos3[0][0]+pos3[1][2];
    double e=pos4[0][0]+pos4[2][1];
    double f=pos5[0][0]+pos5[1][3];
    double g=pos6[0][0]+pos6[3][1];
    double h=pos7[0][0]+pos7[2][3];
    double i=pos8[0][0]+pos8[3][2];
    double j=aPos.x+a+b+c+d;
    double k=aPos.y+e+f+g+h+i;
    gl_Position = vec4(j, k, 0.0, 1.0);
}
