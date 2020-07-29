#version 430 core
in vec3 a_position;
in vec3 a_normal;
out vec3 v_normal;
out vec3 position;

void main()                               
{                
   position = a_position;                         
   gl_Position = vec4(a_position, 1.0); 
   v_normal = a_normal;
}