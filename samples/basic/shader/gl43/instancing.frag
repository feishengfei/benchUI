#version 430 core
 
precision mediump float;

in vec4 vertexColor;
out vec4 fragmentColour;

void main()
{
	fragmentColour = vertexColor;
}
