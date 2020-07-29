#version 430 core

precision mediump int;
precision mediump float;
precision mediump sampler1D;
precision mediump sampler2D;
precision mediump sampler3D;
precision mediump samplerCube;
precision mediump sampler2DArray;
precision mediump samplerBuffer;


layout(early_fragment_tests) in;
//layout(depth_greater) out float gl_FragDepth;

in vec3 vv3colour;
out  vec4 FragColor;

void main()
{
//    gl_FragDepth = gl_FragCoord.z + 0.1;
    FragColor = vec4(vv3colour, 1.0);
}
