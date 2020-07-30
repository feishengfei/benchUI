#version 430 core

precision mediump int;
precision mediump float;
precision mediump sampler1D;
precision mediump sampler2D;
precision mediump sampler3D;
precision mediump samplerCube;
precision mediump sampler2DArray;
precision mediump samplerBuffer;


subroutine vec4 GetOffset();
subroutine uniform GetOffset getoffset;

layout(location = 0) in vec4 a_vertex;
layout(location = 1) in vec4 a_color;
out gl_PerVertex{
    vec4 gl_Position;
};
out vec4 v_color;

subroutine(GetOffset)
vec4 redOffset(){
    return vec4(0.0, 0.5, 0.0, 1.0);
}

subroutine(GetOffset)
vec4 greenOffset(){
    return vec4(-0.5, 0.0, 0.0, 1.0);
}

subroutine(GetOffset)
vec4 blueOffset(){
    return vec4(0.5, 0.0, 0.0, 1.0);
}

void main()
{
	gl_Position =  getoffset() + a_vertex;
	v_color = a_color;
}

