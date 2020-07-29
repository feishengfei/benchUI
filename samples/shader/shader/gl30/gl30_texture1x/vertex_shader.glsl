#version    

in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

//uniform highp sampler1D texUnit0;
uniform sampler1D texUnit0;

void main()
{

	bool results[32];
	for (int i = 0; i < 32; i++){
			results[i] = false;
	}

	vec4 search0 = texture1D(texUnit0, 0.1);
	results[0] = (search0.y == 0.5);

	vec4 search1 = texture1DProj(texUnit0, vec2(0.625, 1.0));
	results[1] = (search1.y == 0.5);

	vec4 search2 = texture1DProj(texUnit0, vec4(0.625, 1.0, 1.0, 1.0));
	results[2] = (search2.y == 0.50);

	vec4 search3 = texture1DLod(texUnit0, 0.75, 1.0);
	results[3] = (search3.y == 0.5);

	vec4 search4 = texture1DProjLod(texUnit0, vec2(0.25, 0.75), 1.0);
	results[4] = (search4.y == 0.5);

	vec4 search5 = texture1DProjLod(texUnit0, vec4(0.25, 0.75, 1.0, 1.0), 1.0);
	results[5] = (search5.y == 0.5);

	gl_Position = vec4(vPosition.x / 16.0, float(results[int(vPosition.x + 16.0)]) / 2.0, vPosition.z, 1.0);

	vfColor = vColor;
	gl_PointSize = 8.0;
}
