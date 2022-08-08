#version 320 es  

in vec3 pos;
precision mediump samplerBuffer;

out vec4 color;
uniform samplerBuffer s;

void main()
{
    vec4 x = texelFetch(s, gl_VertexID);
    gl_Position = vec4(x.xy, 0, 1);
    color = vec4(x.zw, 0, 1);
}
