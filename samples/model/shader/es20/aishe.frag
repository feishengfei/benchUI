

precision lowp float;

varying vec4 vv4colour;
uniform sampler2D u_s2dTexture;

varying vec2 v_v2TexCoord;
void main()
{
    gl_FragColor = vv4colour*texture2D(u_s2dTexture, v_v2TexCoord);
}
