#version 430 core


layout(location = 0) in vec4 vPosition;
out vec2 vpos;
void main()
{
    gl_Position = vPosition;
    vpos = vPosition.xy;
}
