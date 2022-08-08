#version 430 core

out VS_OUT {
    vec4 color;
} vs_out;



void main() {
   const vec4 vertices[] = vec4[](vec4(-0.5,-0.5, 0.0, 1.0),
                                  vec4( 0.5,-0.5, 0.0, 1.0),
                                  vec4( 0.5, 0.5, 0.0, 1.0),
                                  vec4(-0.5, 0.5, 0.0, 1.0));

    const vec4 colors[] = vec4[](vec4(0.0, 0.0, 0.0, 1.0),
                                 vec4(0.0, 0.0, 0.0, 1.0),
                                 vec4(0.0, 0.0, 0.0, 1.0),
                                 vec4(1.0, 1.0, 1.0, 1.0));

    gl_Position = vertices[gl_VertexID % 4];

    vs_out.color = colors[gl_VertexID];
}
