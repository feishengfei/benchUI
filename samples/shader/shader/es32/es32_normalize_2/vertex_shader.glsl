#version   ///GLSL Version 3.20

in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

float myNormalize(float N)
{
		return (N / length(N)) ;
}

vec2 myNormalize(vec2 N)
{
		return (N / length(N)) ;
}

vec3 myNormalize(vec3 N)
{
		return (N / length(N)) ;
}

vec4 myNormalize(vec4 N)
{
		return (N / length(N)) ;
}




void main()
{


	bool a[32] = bool[32](
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false
				);

	a[0] = (myNormalize(-2.0) == myNormalize(-2.0));
	a[1] = (myNormalize(vec2(-1.0, 4.0)) == myNormalize(vec2(-1.0, 4.0)));
	a[2] = (myNormalize(vec3(-1.0, -1.0, 4.0)) == myNormalize(vec3(-1.0, -1.0, 4.0)));
	a[3] = (myNormalize(vec4(-1.0, -1.0, -1.0, 4.0)) == myNormalize(vec4(-1.0, -1.0, -1.0, 4.0)));



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
