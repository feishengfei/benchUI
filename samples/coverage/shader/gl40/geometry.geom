#version 430 core

layout (points) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec3 color;
} gs_in[];

layout (stream = 0) out vec3 fColor;
layout (stream = 0) out vec4 right;
layout (stream = 0) out vec4 left;

void build_house(vec4 position)
{
    fColor = gs_in[0].color;
    gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0);    // 1:左下
    EmitStreamVertex(0);   
    gl_Position = position + vec4( 0.2, -0.2, 0.0, 0.0);    // 2:右下
    EmitStreamVertex(0);
    gl_Position = position + vec4(-0.2,  0.2, 0.0, 0.0);    // 3:左上
    EmitStreamVertex(0);
    gl_Position = position + vec4( 0.2,  0.2, 0.0, 0.0);    // 4:右上
    fColor = vec3(1.0, 1.0, 1.0);
    right = position + vec4( 0.2, 0.0, 0.0, 0.0);
    left = position + vec4( -0.2, 0.0, 0.0, 0.0);
    EmitStreamVertex(0);
    EndStreamPrimitive(0);
}

void main() {    
    build_house(gl_in[0].gl_Position);
}
