/*
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 */

precision mediump float;

//varying vec4 v_v4FillColor;
uniform bool is_sprite;

void main()
{
    if(is_sprite) {
        if(length(gl_PointCoord-vec2(0.5))>0.5)
            discard;
    }
    gl_FragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );
}
