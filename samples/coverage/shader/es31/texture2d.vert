#version 310 es  

out vec2 texCoords;
in vec3 pos;
in vec2 tex;

void main()
{
    texCoords = tex;
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
}
