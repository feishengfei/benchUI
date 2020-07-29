#version    ///GLSL Version 3.20

in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

float myRefract(float I, float N, float eta)
{
	float k = 1.0 - eta * eta * (1.0 - dot(N, I) * dot(N, I));
	if (k < 0.0)
		return 0.0;
	else
		return (eta * I - (eta * dot(N, I) + sqrt(k)) * N) ;
}

vec2 myRefract(vec2 I, vec2 N, float eta)
{
	float k = 1.0 - eta * eta * (1.0 - dot(N, I) * dot(N, I));
	if (k < 0.0)
		return vec2(0.0);
	else
		return (eta * I - (eta * dot(N, I) + sqrt(k)) * N) ;
}

vec3 myRefract(vec3 I, vec3 N, float eta)
{
	float k = 1.0 - eta * eta * (1.0 - dot(N, I) * dot(N, I));
	if (k < 0.0)
		return vec3(0.0);
	else
		return (eta * I - (eta * dot(N, I) + sqrt(k)) * N) ;
}

vec4 myRefract(vec4 I, vec4 N, float eta)
{
	float k = 1.0 - eta * eta * (1.0 - dot(N, I) * dot(N, I));
	if (k < 0.0)
		return vec4(0.0);
	else
		return (eta * I - (eta * dot(N, I) + sqrt(k)) * N) ;
}




void main()
{


	bool a[32] = bool[32](
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false
				);

	a[0] = (myRefract(-1.0, 2.0, 0.25) == refract(-1.0, 2.0, 0.25));
	a[1] = (myRefract(-1.0, -2.0, 0.25) == refract(-1.0, -2.0, 0.25));
	a[2] = (myRefract(vec2(-2.0, -5.0), vec2(3.0, 4.0), 0.25) == refract(vec2(-2.0, -5.0), vec2(3.0, 4.0), 0.25));
	a[3] = (myRefract(vec2(-2.0, -5.0), vec2(-3.0, -4.0), 0.25) == refract(vec2(-2.0, -5.0), vec2(-3.0, -4.0), 0.25));
	a[4] = (myRefract(vec3(-1.0, -1.0, 4.0), vec3(-1.0, -2.0, -5.0), 0.25) == refract(vec3(-1.0, -1.0, 4.0), vec3(-1.0, -2.0, -5.0), 0.25));
	a[5] = (myRefract(vec3(-1.0, -1.0, 4.0), vec3(-1.0, -2.0, -5.0), 0.25) == refract(vec3(-1.0, -1.0, 4.0), vec3(-1.0, -2.0, -5.0), 0.25));
	a[6] = (myRefract(vec4(-1.0, -1.0, -1.0, 4.0), vec4(-1.0, -1.0, -2.0, -5.0), 0.25) == refract(vec4(-1.0, -1.0, -1.0, 4.0), vec4(-1.0, -1.0, -2.0, -5.0), 0.25));
	a[7] = (myRefract(vec4(-1.0, -1.0, -1.0, 4.0), vec4(-1.0, -1.0, -2.0, -5.0), 0.25) == refract(vec4(-1.0, -1.0, -1.0, 4.0), vec4(-1.0, -1.0, -2.0, -5.0), 0.25));


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
