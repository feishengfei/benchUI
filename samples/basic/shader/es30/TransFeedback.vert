#version 300 es  

uniform int tf_pass;
in vec4 piglit_vertex;
flat out int out_pass;
//in vec4 color;
//out vec4 a_color;

void main()
{
	out_pass = tf_pass;
	gl_Position = piglit_vertex;
}

