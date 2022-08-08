#version 430 core
#pragma STDGL invariant(all)
precision lowp float;

uniform sampler2D u_s2dTexture;

in GS_OUT{
    vec4 gv4colour;
    vec2 g_v2TexCoord;
}fs_in;

out vec4 FragColor;

void main()
{
    FragColor = fs_in.gv4colour*texture(u_s2dTexture, fs_in.g_v2TexCoord);
}
