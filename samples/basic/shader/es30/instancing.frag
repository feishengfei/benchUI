#version 300 es
 
precision mediump float;

in vec4 vertexColor;
out vec4 fragmentColour;

void main()
{
	fragmentColour = vertexColor;
}
