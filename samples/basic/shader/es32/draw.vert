#version 320 es
layout(location = 0) in vec3 VertexPosition;
layout(location = 1)in vec3 VertexColor;
precision mediump float;
out vec3 Color;

void main()
{
    Color = VertexColor;
    gl_Position = vec4(VertexPosition,1.0);
}
