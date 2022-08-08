#version 430 core 
in vec3 position;
in vec4 acolor;
uniform UniformBlock { 
    float u1f;
    vec2 u2f;
    vec3 u3f;
    vec4 u4f;
};

out vec4 vcolor;
void main()
{
    vcolor = acolor + u4f;
    float x = position.x + u1f + u2f.x + u3f.x;
    float y = position.y + u2f.y + u3f.y;
    float z = position.z + u3f.z;
    gl_Position = vec4(x, y, z, 1.0);
} 

