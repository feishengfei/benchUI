#version 310 es    

precision highp float;
precision highp int;
precision lowp sampler2D;
precision lowp image2D;

layout(std140, column_major) uniform;
//layout(rgba32f) uniform image2D img1;
layout(location = 0, rgba8) readonly uniform image2D img_output;

out vec4 Color;

void main()
{
	Color = imageLoad(img_output, ivec2(gl_FragCoord.xy));
}
