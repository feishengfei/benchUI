#version 320 es   

precision mediump float;

out  vec4 fColor;

void main()
{
    float a = float(1.0 - gl_FragCoord.z);



    fColor = a * vec4( 1.0, 0.0, 1.0, 1.0 );
}
