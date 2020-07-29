#version  //GLSL Version 3.20; OpenGL es 3.2

precision highp float;

in vec4 vfColor;

centroid in vec4 vfFunc;
centroid in vec3 vfFunc_3;
centroid in vec2 vfFunc_2;
centroid in float vfFunc_1;

out vec4 FragColor;

void main()
{		
	if( 
			( vfFunc == interpolateAtCentroid(vfFunc) ) &&
			( vfFunc_1 == interpolateAtCentroid(vfFunc_1) )	&&	
			( vfFunc_2 == interpolateAtCentroid(vfFunc_2) )	 &&	
			( vfFunc_3 == interpolateAtCentroid(vfFunc_3) )
	   )
		FragColor = vec4(0.0, 1.0, 0.0, 1.0);
	else
		FragColor = vfColor;
}
