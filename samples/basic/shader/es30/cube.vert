#version 300 es  

in vec3 a_position;
in vec3 a_color;
out vec4 Color;

void main()
{
    Color = vec4(a_color.x, a_color.y, a_color.z, 1.0);
    gl_Position = vec4(a_position.x, a_position.y, a_position.z, 1.0);
}
