#version 300 es  
in vec4 a_v4Position;
in vec4 a_v4FillColor;

out vec4 v_v4FillColor;

uniform ivec4 expected_i; 
in ivec4 attr_i; 
uniform uvec4 expected_u; 
in uvec4 attr_u; 

void main()
{
   ivec4 color = ivec4(0, 1, 0, 0);
   uvec4 coloru = uvec4(0, 1, 0, 0);
   if (attr_i == color)
    v_v4FillColor = vec4(1.0,1.0,0.0,0.0);
   else if (attr_u == coloru) 
    v_v4FillColor = vec4(0.0,1.0,1.0,0.0);
   else 
    v_v4FillColor = a_v4FillColor;
    gl_Position = a_v4Position;
}
