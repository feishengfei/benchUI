#version   ///GLSL Version 3.20

in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

float myReflect(float I, float N)
{
		return (I - 2.0 * dot(N, I) * N) ;
}

vec2 myReflect(vec2 I, vec2 N)
{
		return (I - 2.0 * dot(N, I) * N) ;
}

vec3 myReflect(vec3 I, vec3 N)
{
		return (I - 2.0 * dot(N, I) * N) ;
}

vec4 myReflect(vec4 I, vec4 N)
{
		return (I - 2.0 * dot(N, I) * N) ;
}




void main()
{


	bool a[32] = bool[32](
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false
				);

	a[0] = (myReflect(-1.0, 2.0) == reflect(-1.0, 2.0));
	a[1] = (myReflect(-1.0, -2.0) == reflect(-1.0, -2.0));
	a[2] = (myReflect(vec2(-2.0, -5.0), vec2(3.0, 4.0)) == reflect(vec2(-2.0, -5.0), vec2(3.0, 4.0)));
	a[3] = (myReflect(vec2(-2.0, -5.0), vec2(-3.0, -4.0)) == reflect(vec2(-2.0, -5.0), vec2(-3.0, -4.0)));
	a[4] = (myReflect(vec3(-1.0, -1.0, 4.0), vec3(-1.0, -2.0, -5.0)) == reflect(vec3(-1.0, -1.0, 4.0), vec3(-1.0, -2.0, -5.0)));
	a[5] = (myReflect(vec3(-1.0, -1.0, 4.0), vec3(-1.0, -2.0, -5.0)) == reflect(vec3(-1.0, -1.0, 4.0), vec3(-1.0, -2.0, -5.0)));
	a[6] = (myReflect(vec4(-1.0, -1.0, -1.0, 4.0), vec4(-1.0, -1.0, -2.0, -5.0)) == reflect(vec4(-1.0, -1.0, -1.0, 4.0), vec4(-1.0, -1.0, -2.0, -5.0)));
	a[7] = (myReflect(vec4(-1.0, -1.0, -1.0, 4.0), vec4(-1.0, -1.0, -2.0, -5.0)) == reflect(vec4(-1.0, -1.0, -1.0, 4.0), vec4(-1.0, -1.0, -2.0, -5.0)));


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
