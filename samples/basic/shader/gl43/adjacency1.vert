#version 430 core

layout(location=0) in vec4 pos;
layout(location=1) in vec4 colors;

out VS_OUT {
    vec4 color;
} vs_out;



void main() {
    gl_Position = pos;
    vs_out.color = colors;
}
