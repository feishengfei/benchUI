#version  //GLSL Version 3.20; OpenGL es 3.2

precision highp float;
in vec4 vfColor;

layout (std430, binding = 0) buffer BufferObject
{
	int int_var[8];
	uint uint_var[8];
} ssbo ;

out vec4 FragColor;



void main()
{		
	
	bool results[32] = bool[32](
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false
				);
	switch (gl_PrimitiveID){
		case 0:{
					results[0] = (ssbo.uint_var[0] == 10u);
		} break;



		default: break;
	}



	if(results[gl_PrimitiveID] == true)
		FragColor = vec4(0.0, 1.0, 0.0, 1.0);
	else
		FragColor = vfColor;

}
