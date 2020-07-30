#version 310 es    
precision mediump float;
precision mediump image3D;
//#extension GL_ARB_fragment_shader_interlock: require
//layout(pixel_interlock_ordered) in;
layout(rgba32f, binding = 0) writeonly uniform image3D img_output;
//layout(location = 0) uniform image3D img_output;
layout(location = 1) uniform int sample_rate;
smooth in vec4 col_vary;
out vec4 col_out;
void main()
{
	vec4 result = vec4(0.0, 0.0, 0.0, 1.0);
	ivec3 current_sample_coord = ivec3(gl_FragCoord.x, gl_FragCoord.y, gl_SampleID);
	ivec3 result_coord = ivec3(gl_FragCoord.x, gl_FragCoord.y, sample_rate);
	int i;
//	beginInvocationInterlockARB();
	vec4 current_sample_color = imageLoad(img_output, current_sample_coord);
	result.rgb += col_vary.a * col_vary.rgb + (1 - col_vary.a) * current_sample_color.rgb;
	imageStore(img_output, current_sample_coord, result);

	for (i = 0; i < sample_rate; i++) {
		if (i != gl_SampleID) {
			ivec3 sample_coord = ivec3(gl_FragCoord.x, gl_FragCoord.y, i);
			vec4 sample_color = imageLoad(img_output, sample_coord);
			result.rgb += sample_color.rgb;
		}
	}
	result.rgb /= sample_rate;
	imageStore(img_output, result_coord, result);
//	endInvocationInterlockARB();
	col_out = result;
}
