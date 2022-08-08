#version 300 es  

in vec4 a_v4Position;
uniform uint ui1;
uniform uvec2 ui2;
uniform uvec3 ui3;
uniform uvec4 ui4;

out vec4 Color;

void main()
{
    gl_Position = a_v4Position;
    float w = float(ui4.w)/4.0;
    float z = float(ui3.z+ui3.z)/4.0;
    float y = float(ui2.y+ui3.y+ui4.y)/4.0;
    float x = float(ui1+ui2.x+ui3.x+ui4.x)/4.0;
    Color = vec4(w, z, y, x);
}
