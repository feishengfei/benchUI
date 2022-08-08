#version 430 core

precision mediump int;
precision mediump float;
precision mediump sampler1D;
precision mediump sampler2D;
precision mediump sampler3D;
precision mediump samplerCube;
precision mediump sampler2DArray;
precision mediump samplerBuffer;



//uniform mat4 u_m4Projection;

in vec4 a_v4Position;
in vec4 a_v4FillColor;

out vec4 v_v4FillColor;

void main()
{
    v_v4FillColor = a_v4FillColor;
    gl_Position = a_v4Position;
}
