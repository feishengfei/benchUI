#version 320 es
precision mediump float;


layout(location = 0) in vec4 VertexPosition;
layout(location = 1)in vec4 VertexColor;

out vec4 Color;


void main()
{
    Color = VertexColor;
    float a = float(gl_InstanceID);
    vec4 tmp = vec4((VertexPosition.x+a *20.0)/40.0,(VertexPosition.y+a *20.0)/40.0,VertexPosition.z,VertexPosition.w); 	
    gl_Position = tmp;
 
}
