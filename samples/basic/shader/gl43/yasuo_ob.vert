#version 430 core

layout(location=0) uniform vec4 position;
layout(location=1) uniform vec4 eye_vector;
layout(location=2) uniform vec4 light_ambient_color;
layout(location=3) uniform vec4 light_diffuse_color;
layout(location=4) uniform vec4 light_specular_color;
layout(location=5) uniform vec4 material_ambient_color;
layout(location=6) uniform vec4 material_diffuse_color;
layout(location=7) uniform vec4 material_specular_color;
layout(location=8) uniform float material_specular_exponent;
layout(location=9) uniform mat4 mvp;

layout(location=0) in vec4 av4position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 a_v2TexCoord;

const float c_zero=0.0;
const float c_one=1.0;

out vec4 vv4colour;
out vec2 v_v2TexCoord;

void main()
{
    v_v2TexCoord = a_v2TexCoord;
	//vec3 normalTrans= normalize(gl_NormalMatrix * normalize(normal)); 
	vec3 normalTrans=normalize(normal); 
	vec3 lightDir = normalize(vec3(position.xyz)); 

	vec3 halfVector=normalize(normalize(eye_vector.xyz)+lightDir);

	vec4 computed_color=vec4(c_zero,c_zero,c_zero,c_zero);

	float ndotl;
	float ndoth;

	ndotl=max(c_zero,dot(normalTrans,lightDir));
	ndoth=max(c_zero,dot(normalTrans,halfVector));
	
	computed_color+=(light_ambient_color*material_ambient_color);
	computed_color+=(ndotl*material_diffuse_color*light_diffuse_color);
	if(ndoth>0.0){
	computed_color+=(pow(ndoth,material_specular_exponent)*light_specular_color*material_specular_color);
	}
	
    vv4colour = computed_color;
    gl_Position = mvp * av4position;
}
