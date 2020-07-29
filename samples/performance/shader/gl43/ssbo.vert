#version 430 core

layout(location=0) in vec2 position;

struct vertex{
    vec4 color;
};

layout(std430) buffer my_vertices{
    vertex vertices[];
};

out VS_OUT{
    vec4 color;
}vs_out;

void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
    vs_out.color = vertices[gl_VertexID].color;
};
