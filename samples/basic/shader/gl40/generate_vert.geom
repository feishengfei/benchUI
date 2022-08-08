#version 430 core

layout(points) in;
layout(points, max_vertices = 7) out;

in VS_OUT {
    float angle;
} gs_in[];

out vec2 pos;

void main() { 
    float x = sin(gs_in[0].angle);
    float y = cos(gs_in[0].angle);
    pos = vec2(x,y);
    EmitVertex();
    EndPrimitive();
}
