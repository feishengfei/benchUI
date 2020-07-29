#version  //GLSL Version 3.20; OpenGL es 3.2

precision highp float;

in vec4 vfColor;
in vec4 vfFunc;

out vec4 FragColor;

void main()
{		
	if( 
			( abs((dFdx(vfFunc)).x - 5.0/200.0) < (5.0 / 200.0 * 0.001) ) && 
			( abs((dFdx(vfFunc.xyz)).x - 5.0/200.0) < (5.0 / 200.0 * 0.001) ) &&
			( abs((dFdx(vfFunc.xy)).x - 5.0/200.0) < (5.0 / 200.0 * 0.001) ) &&	
			( abs((dFdx(vfFunc.xy)).x - 5.0/200.0) < (5.0 / 200.0 * 0.001) ) &&	
			( abs(dFdx(vfFunc.x) - 5.0/200.0) < (5.0 / 200.0 * 0.001) ) &&
			
			( abs(dFdy(vfFunc.x) - 2.0/200.0) < (2.0 / 200.0 * 0.001) ) &&
			( abs((dFdy(vfFunc)).x - 2.0/200.0) < (2.0 / 200.0 * 0.001) ) && 
			( abs((dFdy(vfFunc.xyz)).x - 2.0/200.0) < (2.0 / 200.0 * 0.001) ) &&
			( abs((dFdy(vfFunc.xy)).x - 2.0/200.0) < (2.0 / 200.0 * 0.001) ) &&	
			( abs((dFdy(vfFunc.xy)).x - 2.0/200.0) < (2.0 / 200.0 * 0.001) ) &&

			( fwidth(vfFunc.xyz)  == abs(dFdx(vfFunc.xyz)) + abs(dFdy(vfFunc.xyz)) ) &&
			( fwidth(vfFunc.xy)  == abs(dFdx(vfFunc.xy)) + abs(dFdy(vfFunc.xy)) ) &&
			( fwidth(vfFunc.x)  == abs(dFdx(vfFunc.x)) + abs(dFdy(vfFunc.x)) ) &&
			( fwidth(vfFunc)  == abs(dFdx(vfFunc)) + abs(dFdy(vfFunc)) )

	   )
		FragColor = vec4(0.0, 1.0, 0.0, 1.0);
	else
		FragColor = vfColor;
}
