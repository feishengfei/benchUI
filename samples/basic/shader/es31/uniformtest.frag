#version 310 es                                  

precision mediump float;

uniform vec4 v_vFillColor;
uniform float v_vuf1f;
uniform vec2 v_vuf2f;
uniform vec3 v_vuf3f;

uniform ivec4 v_iFillColor;
uniform int v_iuf1f;
uniform ivec2 v_iuf2f;
uniform ivec3 v_iuf3f;

uniform ivec4 v_uiFillColor;
uniform int v_uiuf1f;
uniform ivec2 v_uiuf2f;
uniform ivec3 v_uiuf3f;

//in vec4 v_vFillColor;
//in uvec4 Color;
out vec4 Color;
//out vec4 Color;

void main()
{
	//Color = uvec4(v_uiuf2f,v_uiuf2f);	
	
	//Color = ivec4 (v_iuf2f,v_iuf2f);
	//Color = ivec4 (v_iuf3f,v_iuf1f);

	//Color = ivec4 (v_iFillColor);	
	//Color = vec4 (v_vuf3f,v_vuf1f);	
	Color = v_vFillColor;

}
