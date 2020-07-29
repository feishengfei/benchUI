/*
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 */

precision lowp float;

varying vec3 vv3colour;

void main()
{
    gl_FragColor = vec4(vv3colour, 1.0);
}
