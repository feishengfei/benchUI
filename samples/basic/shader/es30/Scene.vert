#version 300 es                                   
uniform mat4 u_mvpMatrix;                         
uniform mat4 u_mvpLightMatrix;                    
layout(location = 0) in vec4 a_position;          
layout(location = 1) in vec4 a_color;             
out vec4 v_color;                                 
out vec4 v_shadowCoord;                           
void main()                                       
{                                                 
   v_color = a_color;                             
   gl_Position = u_mvpMatrix * a_position;        
   v_shadowCoord = u_mvpLightMatrix * a_position; 
                                                  
   // transform from [-1,1] to [0,1];             
   v_shadowCoord = v_shadowCoord * 0.5 + 0.5;     
}
