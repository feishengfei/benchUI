#version 430 core

precision mediump int;
precision mediump float;
precision mediump sampler1D;
precision mediump sampler2D;
precision mediump sampler3D;
precision mediump samplerCube;
precision mediump sampler2DArray;
precision mediump samplerBuffer;


layout(location = 0) in vec4 pos;

out gl_PerVertex{
    vec4 gl_Position;
};

void main()
{
    gl_Position = pos;
}

