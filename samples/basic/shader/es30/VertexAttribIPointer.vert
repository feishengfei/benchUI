#version 300 es  
 
in vec4 a_v4Position; 
uniform ivec4 expected_i; 
in ivec4 attr_i; 
uniform uvec4 expected_u; 
in uvec4 attr_u; 
out vec4 color; 

void main()
{
   gl_Position = a_v4Position; 
   if (attr_i == expected_i && attr_u == expected_u) 
      color = vec4(0, 1, 0, 0); // good! 
   else 
      color = vec4(1, 0, 0, 0); // bad!
}
