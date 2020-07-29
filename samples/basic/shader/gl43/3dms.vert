#version 430 core

layout(location = 0) in vec4 a_position;
out vec2 texCoord;
void main()
{
   gl_Position = a_position;
   texCoord = a_position.xy*0.5 + 0.5;
}

