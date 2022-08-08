#version 430 core

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

