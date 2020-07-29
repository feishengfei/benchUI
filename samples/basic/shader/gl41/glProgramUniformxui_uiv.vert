#version 430 core

layout(location = 0) in vec4 pos;

out gl_PerVertex{
    vec4 gl_Position;
};

void main()
{
    gl_Position = pos;
}

