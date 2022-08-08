#version 430 core core
precision mediump float;
in vec2 position;
uniform vec2 offsets[100];
void main()
{
    vec2 offset = offsets[gl_InstanceID];
    gl_Position = vec4(position+offset,0.0,1.0);
}
