#version 430 core

precision lowp float;

in GS_OUT{
    vec4 color;
}fs_in;

out vec4 FragColor;

void main()
{
    FragColor = fs_in.color;
}
