#version  //GLSL Version 3.20; OpenGL es 3.2

precision highp float;

in vec4 vfColor;

in vec4 vfFunc;
in vec3 vfFunc_3;
in vec2 vfFunc_2;
in float vfFunc_1;

out vec4 FragColor;

void main()
{		
	if( 
/*
//			(interpolateAtOffset(vfFunc, vec2(-0.5, 0.0)) != interpolateAtOffset(vfFunc, vec2(0.5, 0.0)) )
//		&& ((interpolateAtOffset(vfFunc, vec2(0.0, 0.0)) - 0.5 * (interpolateAtOffset(vfFunc, vec2(-0.5, 0.0)) + interpolateAtOffset(vfFunc, vec2(0.5, 0.0))) ).x < 0.1 )
//		&& ((interpolateAtOffset(vfFunc, vec2(0.0, 0.0))).x + (interpolateAtOffset(vfFunc, vec2(0.0, 0.0))).x - (interpolateAtOffset(vfFunc, vec2(-0.5, 0.0))).x - (interpolateAtOffset(vfFunc, vec2(0.5, 0.0))).x ) < 0.01 
//		&&	(interpolateAtOffset(vfFunc_3, vec2(-0.5, 0.0)) != interpolateAtOffset(vfFunc_3, vec2(0.5, 0.0)) ) 
//		&&	((interpolateAtOffset(vfFunc_3, vec2(0.0, 0.0)) - 0.5 * (interpolateAtOffset(vfFunc_3, vec2(-0.5, 0.0)) + interpolateAtOffset(vfFunc_3, vec2(0.5, 0.0))) ).x < 0.001 ) 

//		&&	(interpolateAtOffset(vfFunc_2, vec2(-0.5, 0.0)) != interpolateAtOffset(vfFunc_2, vec2(0.5, 0.0)) ) 
//		&&	((interpolateAtOffset(vfFunc_2, vec2(0.0, 0.0)) - 0.5 * (interpolateAtOffset(vfFunc_2, vec2(-0.5, 0.0)) + interpolateAtOffset(vfFunc_2, vec2(0.5, 0.0))) ).x < 0.001 ) 

//		&&	(interpolateAtOffset(vfFunc_1, vec2(-0.5, 0.0)) != interpolateAtOffset(vfFunc_1, vec2(0.5, 0.0)) )
//		&&	((interpolateAtOffset(vfFunc_1, vec2(0.0, 0.0)) - 0.5 * (interpolateAtOffset(vfFunc_1, vec2(-0.5, 0.0)) + interpolateAtOffset(vfFunc_1, vec2(0.5, 0.0))) ) < 0.001 )
//		abs(((interpolateAtOffset(vfFunc, vec2(1.0, 0.0))).x) - ((interpolateAtOffset(vfFunc, vec2(0.0, 0.0))).x) - 1.0) < 0.5
//		(interpolateAtOffset(vfFunc, vec2(0.0, 0.0))).x == 1.5
        abs((interpolateAtOffset(vfFunc, vec2(0.4, 0.0))).x  -  (interpolateAtOffset(vfFunc, vec2(0.0, 0.0))).x - 0.4) < 0.00001
*/

			(interpolateAtOffset(vfFunc, vec2(0.0, 0.0)) == vfFunc)
		&&	(interpolateAtOffset(vfFunc_3, vec2(0.0, 0.0)) == vfFunc_3)
		&& (interpolateAtOffset(vfFunc_2, vec2(0.0, 0.0)) == vfFunc_2)
		&& (interpolateAtOffset(vfFunc_1, vec2(0.0, 0.0)) == vfFunc_1)	
		&&	((interpolateAtOffset(vfFunc, vec2(0.0, 0.0))).x != 0.5)
		&& (interpolateAtOffset(vfFunc_1, vec2(0.0, 0.0)) != 9.5)	

	   )
		FragColor = vec4(0.0, 1.0, 0.0, 1.0);
	else
		FragColor = vfColor;
}
