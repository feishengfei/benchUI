/*
 * This proprietary software may be used only as
 * authorised by a licensing agreement from Botson Limited
 * (C) COPYRIGHT 2019 Botson Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from Botson Limited.
 */
 
 //light
 uniform vec4 position;
 uniform vec4 eye_vector;
 uniform vec4 light_ambient_color;
 uniform vec4 light_diffuse_color;
 uniform vec4 light_specular_color;

 //material
 uniform vec4 material_ambient_color;
 uniform vec4 material_diffuse_color;
 uniform vec4 material_specular_color;
 uniform float material_specular_exponent;

 const float c_zero=0.0;
 const float c_one=1.0;


attribute vec4 av4position;
attribute vec3 normal;

uniform mat4 mvp;
varying vec4 vv4colour;
attribute vec2 a_v2TexCoord;

varying vec2 v_v2TexCoord;
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
