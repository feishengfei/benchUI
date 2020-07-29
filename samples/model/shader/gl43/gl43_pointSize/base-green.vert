#version 430 core   //version under 1.4 

#extension GL_ARB_explicit_uniform_location : enable
precision mediump float;

//layout(location = 0) uniform mat4 mv_matrix;
in vec4 a_v4Position;

void main()
{
    gl_Position = a_v4Position;// * mv_matrix;
}
