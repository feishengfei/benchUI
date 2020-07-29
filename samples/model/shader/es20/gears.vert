/*
 * This proprietary software may be used only as
 * authorised by a licensing agreement from Botson Limited
 * (C) COPYRIGHT 2019 Botson Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from Botson Limited.
 */

attribute vec3 av3position;
attribute vec3 av3normal;

uniform mat4 frustum;
uniform vec4 materal;
uniform mat4 modelview;

varying vec4 vv4colour;
//varying float diffuse;

void main()
{
/*    vec4 lightposition = vec4(5.0, 5.0, 10.0, 0.0);
    vec4 tnorm = normalize(modelview * vec4(av3normal, 1.0));
    vec3 s = normalize(vec3(lightposition));
    float diffuse = max(dot(s,tnorm.xyz), 1.0);
*/

    vec4 LightPosition = vec4(5.0, 5.0, 10.0, 0.0);
    vec3 DirectionLight = normalize(LightPosition.xyz);

    vec4 tnorm = modelview * vec4(av3normal, 0.0);
    vec3 Normal = normalize(tnorm.xyz);

//    vec3 s = normalize(vec3(lightposition));
    float diffuse = max(0.0, dot(Normal,DirectionLight));

    mat4 mvp = frustum * modelview;
    vv4colour = diffuse * materal;
    gl_Position = mvp * vec4(av3position, 1.0);
}
