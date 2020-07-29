#version   ///GLSL Version 4.5

layout(points) in;
layout(points, max_vertices = 4) out;

layout (stream = 0) out vec4 rf_position;

uniform highp sampler2D texUnit0;
uniform highp isampler2D texUnit1;
uniform highp usampler2D texUnit2;
uniform highp sampler3D texUnit3;

uniform highp isampler3D texUnit4;
uniform highp usampler3D texUnit5;
uniform highp sampler2DArray texUnit6;
uniform highp isampler2DArray texUnit7;

uniform highp usampler2DArray texUnit8;
uniform highp samplerCube texUnit9;
uniform highp isamplerCube texUnit10;
uniform highp usamplerCube texUnit11;

void main()
{
    gl_Position = gl_in[0].gl_Position;

    int search0 = textureQueryLevels(texUnit0);
    int search1 = textureQueryLevels(texUnit1);
    int search2 = textureQueryLevels(texUnit2);
    int search3 = textureQueryLevels(texUnit3);
    int search4 = textureQueryLevels(texUnit4);
    int search5 = textureQueryLevels(texUnit5);
    int search6 = textureQueryLevels(texUnit6);
    int search7 = textureQueryLevels(texUnit7);
    int search8 = textureQueryLevels(texUnit8);
    int search9 = textureQueryLevels(texUnit9);
    int search10 = textureQueryLevels(texUnit10);
    int search11 = textureQueryLevels(texUnit11);

    rf_position = vec4(search0, search1, search2, search3);
    EmitStreamVertex(0);
    rf_position = vec4(search4, search5, search6, search7);
    EmitStreamVertex(0);
    rf_position = vec4(search8, search9, search10, search11);
    EmitStreamVertex(0);

    EndStreamPrimitive(0);
}
