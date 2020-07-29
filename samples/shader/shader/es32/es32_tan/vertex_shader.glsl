#version 

precision mediump float;
in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

void main()
{
	float angle = radians(vPosition.x);

	float y1 = tan(angle);
	vec2 y2 = tan(vec2(1.0, angle));
	vec3 y3 = tan(vec3(1.0, 1.0, angle));
	vec4 y4 = tan(vec4(1.0, 1.0, 1.0, angle));
	float y_average = 0.25 * (y1 + y2.y + y3.z + y4.w);

	gl_Position = vec4(angle/3.1416, y_average/10.0, vPosition.z, 1.0); 
	vfColor = vColor;
	gl_PointSize = 8.0;

}
