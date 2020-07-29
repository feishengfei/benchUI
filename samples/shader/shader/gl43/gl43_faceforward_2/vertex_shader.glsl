#version   ///GLSL Version 3.20

in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

float myFaceforward(float N, float I, float Nref)
{
	if( dot(Nref, I) < 0.0 ) 
		return N ;
	else 
		return ((-1.0) * N) ;
}

vec2 myFaceforward(vec2 N, vec2 I, vec2 Nref)
{
	if( dot(Nref, I) < 0.0 )  
		return N ;
	else 
		return ((-1.0) * N) ;
}

vec3 myFaceforward(vec3 N, vec3 I, vec3 Nref)
{
	if( dot(Nref, I) < 0.0 )
		return N ;
	else 
		return ((-1.0) * N) ;
}

vec4 myFaceforward(vec4 N, vec4 I, vec4 Nref)
{
	if( dot(Nref, I) < 0.0 )
		return N ;
	else 
		return ((-1.0) * N) ;
}




void main()
{


	bool a[32] = bool[32](
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false
				);

	a[0] = (myFaceforward(-1.0, 2.0, 3.0) == faceforward(-1.0, 2.0, 3.0));
	a[1] = (myFaceforward(-1.0, -2.0, 3.0) == faceforward(-1.0, -2.0, 3.0));
	a[2] = (myFaceforward(vec2(-1.0, 4.0), vec2(-2.0, -5.0), vec2(3.0, 4.0)) == myFaceforward(vec2(-1.0, 4.0), vec2(-2.0, -5.0), vec2(3.0, 4.0)));
	a[3] = (myFaceforward(vec2(-1.0, 4.0), vec2(-2.0, -5.0), vec2(-3.0, -4.0)) == myFaceforward(vec2(-1.0, 4.0), vec2(-2.0, -5.0), vec2(-3.0, -4.0)));
	a[4] = (myFaceforward(vec3(-1.0, -1.0, 4.0), vec3(-1.0, -2.0, -5.0), vec3(2.0, 3.0, 4.0)) == myFaceforward(vec3(-1.0, -1.0, 4.0), vec3(-1.0, -2.0, -5.0), vec3(2.0, 3.0, 4.0)));
	a[5] = (myFaceforward(vec3(-1.0, -1.0, 4.0), vec3(-1.0, -2.0, -5.0), vec3(-2.0, -3.0, -4.0)) == myFaceforward(vec3(-1.0, -1.0, 4.0), vec3(-1.0, -2.0, -5.0), vec3(-2.0, -3.0, -4.0)));
	a[6] = (myFaceforward(vec4(-1.0, -1.0, -1.0, 4.0), vec4(-1.0, -1.0, -2.0, -5.0), vec4(1.0, 2.0, 3.0, 4.0)) == myFaceforward(vec4(-1.0, -1.0, -1.0, 4.0), vec4(-1.0, -1.0, -2.0, -5.0), vec4(1.0, 2.0, 3.0, 4.0)));
	a[7] = (myFaceforward(vec4(-1.0, -1.0, -1.0, 4.0), vec4(-1.0, -1.0, -2.0, -5.0), vec4(-1.0, -2.0, -3.0, -4.0)) == myFaceforward(vec4(-1.0, -1.0, -1.0, 4.0), vec4(-1.0, -1.0, -2.0, -5.0), vec4(-1.0, -2.0, -3.0, -4.0)));


	gl_Position = vec4(vPosition.x / 16.0, float(a[gl_VertexID]) / 2.0, vPosition.z, 1.0);
//	gl_Position = vec4(vPosition.x / 16.0, float(((~x) >> gl_VertexID) & 0x1) / 2.0, vPosition.z, 1.0);


	if(gl_VertexID < 16)
		vfColor = vColor;
	else 
		vfColor = vColor * 0.5;	
		
	gl_PointSize = 8.0;
}

// 0x10000u = 2^16
// in packUnorm2x16(vec2(vPosition.x, 0.5)), vPosition.x is the lower part, 0.5 is the higher part
