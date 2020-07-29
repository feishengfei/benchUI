#version 430 core

precision lowp float;


in GS_OUT{
    vec4 gv4colour;
}fs_in;

out vec4 FragColor;

void main()
{
    FragColor = fs_in.gv4colour;
}
