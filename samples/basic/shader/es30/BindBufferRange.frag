#version 300 es

precision mediump float;
 
/* Output color variable. */
out vec4 color;

void main()
{
	/* Set yellow color for a cube representing light source. */
	color = vec4(1.0, 1.0, 0.0, 0.6);
}
