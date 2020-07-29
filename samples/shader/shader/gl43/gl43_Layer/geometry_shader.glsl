#version 320 es //GLSL Version 3.20; OpenGL es 3.2

layout(triangles) in;
layout(triangle_strip, max_vertices = 6) out;

in vec4 norm[];
in vec4 object_color[];

out vec4 gColor;

void main()
{
		gl_Layer = 0;
		for(int i = 0; i < 3; i++)
		{
			gl_Position = gl_in[i].gl_Position;
			gColor = object_color[i];
			EmitVertex();
		}
		EndPrimitive();

		gl_Layer = 1;	
		for(int j = 0; j < 3; j++)
		{
					
			gl_Position = gl_in[j].gl_Position + 0.2 * normalize(norm[j]);
			gColor = object_color[j];
			EmitVertex();
		}
		EndPrimitive();

//	gl_Layer = gl_InvocationID;
	
}
