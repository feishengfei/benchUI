#version 430 core

layout(points) in;
layout(points, max_vertices = 4) out;

layout (stream = 0) out vec4 rf_position;
layout (stream = 1) out vec4 lf_position;

void main() { 
    if(gl_in[0].gl_Position.x < 0.0)
    {
        rf_position = gl_in[0].gl_Position + vec4(-0.2, -0.2, 0.0, 0.0);
        EmitStreamVertex(0);
        EndStreamPrimitive(0);
    }
    else
    {
        lf_position = gl_in[0].gl_Position + vec4(-0.2, -0.1, 0.0, 0.0);
        EmitStreamVertex(1);
        EndStreamPrimitive(1);
    }

}
