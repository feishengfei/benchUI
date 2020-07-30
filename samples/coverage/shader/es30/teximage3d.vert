#version 300 es  

out vec3 texCoords;
in vec3 pos;
in vec3 tex;

void main()
{
    texCoords = tex;
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
}

