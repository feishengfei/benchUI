/*
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 */

attribute vec4 a_v4Position;

uniform float u1f;
uniform float u1fv;
uniform vec2 u2f;
uniform vec2 u2fv;
uniform vec3 u3f;
uniform vec3 u3fv;
uniform vec4 u4f;
uniform vec4 u4fv;
uniform mat2 mat2f;
uniform mat3 mat3f;

uniform int u1i;
uniform int u1iv;
uniform ivec2 u2i;
uniform ivec2 u2iv;
uniform ivec3 u3i;
uniform ivec3 u3iv;
uniform ivec4 u4i;
uniform ivec4 u4iv;

varying vec4 v_v4FillColor;

void main()
{
    ivec4 FillColor = ivec4(u1i,0,0,0) + ivec4(u1iv,0,0,0) + ivec4(u2i,0,0) + ivec4(u2iv,0,0) + ivec4(u3i,0) + ivec4(u3iv,0) + u4i + u4iv;
    v_v4FillColor = vec4(float(FillColor[0]/8), float(FillColor[1]/8), float(FillColor[2]/8), float(FillColor[3]/8));
    vec4 tmp = vec4(u1f,0.0,0.0,0.0) + vec4(u1fv,0.0,0.0,0.0) + vec4(u2f,0.0,0.0) + vec4(u2fv,0.0,0.0) + vec4(u3f,0.0) + vec4(u3fv,0.0) + u4f + u4fv;
    mat4 ScaleMat = mat4(tmp[3], 0.0, 0.0, 0.0,  
			0.0, tmp[2], 0.0, 0.0,
			0.0, 0.0, tmp[1], 0.0,
			0.0, 0.0, 0.0, tmp[0]
     );
    mat4 TransMat = mat4(mat3f[0][0], mat3f[0][1], mat3f[0][2], 0.0,  
			mat3f[1][0], mat3f[1][1], mat3f[1][2], 0.0,
			mat3f[2][0], mat3f[2][1], mat3f[2][2], 0.0,
			mat2f[0][0], mat2f[1][0], mat2f[0][1], mat2f[1][1] 
     );

    gl_Position = ScaleMat * TransMat * a_v4Position;
}
