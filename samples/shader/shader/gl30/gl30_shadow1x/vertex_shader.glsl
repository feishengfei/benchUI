#version    

in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

uniform highp sampler1DShadow texUnit0;

void main()
{

	bool results[32];
	for (int i = 0; i < 32; i++){
			results[i] = false;
	}

	vec4 search0 = shadow1D(texUnit0, vec3(0.625, 0.375, 1.0));
	results[0] = (search0.y == 0.5);

	vec4 search1 = shadow1DProj(texUnit0, vec4(0.625, 0.375, 0.0, 1.0));
	results[1] = (search1.y == 0.5);

	vec4 search2 = shadow1DProj(texUnit0, vec4(0.625, 0.375, 1.0, 1.0));
	results[2] = (search2.y == 0.5);

	vec4 search3 = shadow1DLod(texUnit0, vec3(0.75, 0.25, 1.0), 1.0);
	results[3] = (search3.y == 0.5);

	vec4 search4 = shadow1DProjLod(texUnit0, vec4(0.25, 0.75, 0.0, 1.0), 1.0);
	results[4] = (search4.y == 0.5);

	vec4 search5 = shadow1DProjLod(texUnit0, vec4(0.25, 0.75, 1.0, 1.0), 1.0);
	results[5] = (search5.y == 0.5);

	gl_Position = vec4(vPosition.x / 16.0, float(results[int(vPosition.x + 16.0)]) / 2.0, vPosition.z, 1.0);

	vfColor = vColor;	
	gl_PointSize = 8.0;
}
